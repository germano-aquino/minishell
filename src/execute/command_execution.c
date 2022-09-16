/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:45:49 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/16 16:10:20 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	call_execve_or_builtin(t_minishell *data, char **envp, int index)
{
	if (!is_builtin(data->cmd.cmd_path[index]))
	{
		if (execve(data->cmd.cmd_path[index], data->cmd.args[index], envp) != 0)
		{
			ft_free_matrix((void *)&envp);
			exit_perror(data, *data->cmd.args[index], "execve", EXIT_FAILURE);
		}
	}
	ft_free_matrix((void *)&envp);
	check_builtin(data, index, TRUE);
}

static void	parent_routine(t_minishell *data, t_workspace *vars, int index)
{
	close(vars->fd[index][IN]);
	close(vars->fd[index][OUT]);
	if (data->cmd.connector[index] == AND || data->cmd.connector[index] == OR)
		wait_conditional_child(vars, index);
	else
		++data->should_wait;
}

static void	child_routine(t_minishell *data, t_workspace *vars, int index)
{
	int	i;

	trigger_signal(FALSE, &child_handler);
	dup2(vars->fd[index][IN], STDIN);
	dup2(vars->fd[index][OUT], STDOUT);
	dup2(data->fd_err, STDERR);
	i = -1;
	while (++i < data->cmd.cmds_amount)
	{
		close(vars->fd[i][IN]);
		close(vars->fd[i][OUT]);
	}
	close(data->fd_err);
	ft_memfree((void *)&vars->pid);
	ft_memfree((void *)&vars->depth);
	ft_memfree((void *)&vars->wstatus);
	ft_free_matrix((void *)&vars->fd);
	call_execve_or_builtin(data, get_env_from_ht(&data->env), index);
}

static void	create_fork(t_minishell *data, t_workspace *vars, int *index)
{
	if (*index > 0 && has_conditional_error(data, vars, *index))
	{
		skip_pipeline(data, vars, index);
		return ;
	}
	if (has_path_error(data, vars, data->cmd.cmd_path[*index], *index))
	{
		close(vars->fd[*index][IN]);
		close(vars->fd[*index][OUT]);
		return ;
	}
	vars->pid[*index] = fork();
	if (vars->pid[*index] == 0)
		child_routine(data, vars, *index);
	else if (vars->pid[*index] < 0)
		return ;
	else
		parent_routine(data, vars, *index);
}

void	execute(t_minishell *data)
{
	t_workspace	vars;
	int			index;

	if (data->cmd.cmds_amount == 0)
		return ;
	trigger_signal(FALSE, &cmd_handler);
	initialize_workspace(data, &vars);
	index = -1;
	while (++index < data->cmd.cmds_amount)
		create_fork(data, &vars, &index);
	wait_child(&vars, data->cmd.cmds_amount, data->should_wait);
	ft_memfree((void *)&vars.pid);
	ft_memfree((void *)&vars.depth);
	ft_memfree((void *)&vars.wstatus);
	ft_free_matrix((void *)&vars.fd);
}
