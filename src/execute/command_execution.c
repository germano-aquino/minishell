/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:45:49 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/12 20:07:15 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_execve_or_builtin(t_minishell *data, char **envp, int index)
{
	if (validate_path(data, data->cmd.cmd_path[index], index))
	{
		ft_free_matrix((void *)&envp);
		exit_free(data, g_exit_value);
	}
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

void	execute_command(t_minishell *data, t_workspace *vars, int index)
{
	int		i;

	vars->pid[index] = fork();
	if (vars->pid[index] == 0)
	{
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
		ft_free_matrix((void *)&vars->fd);
		call_execve_or_builtin(data, get_env_from_ht(&data->env), index);
	}
	close(vars->fd[index][IN]);
	close(vars->fd[index][OUT]);
}

void	wait_child(t_minishell *data, t_workspace *vars)
{
	int	index;
	int	status;

	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		if (vars->pid[index])
		{
			waitpid(vars->pid[index], &status, 0);
			if (WIFEXITED(status))
				g_exit_value = WEXITSTATUS(status);
			else
				handle_dead_child(status);
		}
	}
}

void	execute_forks(t_minishell *data)
{
	t_workspace	vars;
	int			index;

	if (data->cmd.cmds_amount == 0)
		return ;
	trigger_signal(FALSE, &cmd_handler);
	initialize_pipes_and_pid(data, &vars);
	index = -1;
	while (++index < data->cmd.cmds_amount)
		execute_command(data, &vars, index);
	wait_child(data, &vars);
	ft_memfree((void *)&vars.pid);
	ft_free_matrix((void *)&vars.fd);
}
