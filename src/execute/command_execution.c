/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:45:49 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/15 12:06:04 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_execve_or_builtin(t_minishell *data, char **envp, int index)
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

void	execute_command(t_minishell *data, t_workspace *vars, int index)
{
	char	**envp;
	int		i;

	vars->pid[index] = fork();
	if (vars->pid[index] == 0)
	{
		trigger_signal(FALSE, &child_handler);
		envp = get_env_from_ht(&data->env);
		dup2(vars->fd[index][IN], STDIN);
		dup2(vars->fd[index][OUT], STDOUT);
		i = -1;
		while (++i < data->cmd.cmds_amount)
		{
			close(vars->fd[i][IN]);
			close(vars->fd[i][OUT]);
		}
		ft_memfree((void *)&vars->pid);
		ft_free_matrix((void *)&vars->fd);
		call_execve_or_builtin(data, envp, index);
	}
	else
	{
		close(vars->fd[index][IN]);
		close(vars->fd[index][OUT]);
	}
}

void	wait_child(t_minishell *data, t_workspace *vars)
{
	int	index;

	index = -1;
	while (++index < data->cmd.cmds_amount)
		if (vars->pid[index])
			waitpid(vars->pid[index], &data->child_exit_code, 0);
	if (vars->pid[index - 1] && WIFEXITED(data->child_exit_code))
		g_exit_value = WEXITSTATUS(data->child_exit_code);
	if (!data->cmd.cmd_path[data->cmd.cmds_amount - 1])
		g_exit_value = EXIT_NOT_FOUND;
}

void	execute_forks(t_minishell *data)
{
	t_workspace	vars;
	int			index;

	if (!*data->cmd.args)
		return ;
	trigger_signal(FALSE, &cmd_handler);
	initialize_pipes_and_pid(data, &vars);
	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		if (validate_path(data, data->cmd.cmd_path[index], index) != 0)
		{
			close(vars.fd[index][IN]);
			close(vars.fd[index][OUT]);
			if (g_exit_value == EXIT_SUCCESS)
				g_exit_value = EXIT_FAILURE;
		}
		else
			execute_command(data, &vars, index);
	}
	wait_child(data, &vars);
	ft_memfree((void *)&vars.pid);
	ft_free_matrix((void *)&vars.fd);
}
