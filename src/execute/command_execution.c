/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:45:49 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/10 23:45:51 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_execve_or_builtin(
	t_minishell *data, t_workspace *vars, char **envp, int index)
{
	free(vars->pid);
	if (!is_builtin(data->cmd.cmd_path[index]))
	{
		if (execve(data->cmd.cmd_path[index],
				data->cmd.args[index], envp) == -1)
		{
			ft_free_matrix((void *) &envp);
			perror("minishell: execve");
			exit_free(data, EXIT_FAILURE);
		}
	}
	ft_free_matrix((void *) &envp);
	check_builtin(data, index, TRUE);
}

void	child_task(t_minishell *data, t_workspace *vars, int index)
{
	char	**envp;
	int		i;

	trigger_signal(0, &child_handler);
	envp = get_env_from_ht(&data->env);
	dup2(vars->fd[index][0], STDIN);
	dup2(vars->fd[index][1], STDOUT);
	i = -1;
	while (++i < data->cmd.cmds_amount)
	{
		close(vars->fd[i][0]);
		close(vars->fd[i][1]);
	}
	ft_free_matrix((void *)&vars->fd);
	call_execve_or_builtin(data, vars, envp, index);
}

void	exec_cmd(t_minishell *data, t_workspace *vars, int index)
{
	vars->pid[index] = fork();
	if (vars->pid[index] == 0)
		child_task(data, vars, index);
	else
	{
		close(vars->fd[index][0]);
		close(vars->fd[index][1]);
	}
}

void	close_unused_fds(t_minishell *data, t_workspace *vars, int index)
{
	close(vars->fd[index][0]);
	close(vars->fd[index][1]);
	data->ext_val = EXIT_FAILURE;
}

void	exec_cmds(t_minishell *data)
{
	t_workspace	vars;
	int			index;

	trigger_signal(0, &cmd_handler);
	initialize_pipes_and_pid(data, &vars);
	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		if (!data->cmd.cmd_path[index])
			command_not_found(data, index);
		else if (!*data->cmd.cmd_path[index])
			close_unused_fds(data, &vars, index);
		else
			exec_cmd(data, &vars, index);
	}
	index = -1;
	while (++index < data->cmd.cmds_amount)
		if (vars.pid[index])
			waitpid(vars.pid[index], &data->child_exit_code, 0);
	if (vars.pid[index - 1] && WIFEXITED(data->child_exit_code))
		data->ext_val = WEXITSTATUS(data->child_exit_code);
	ft_memfree((void *)&vars.pid);
	ft_free_matrix((void *)&vars.fd);
	if (!data->cmd.cmd_path[data->cmd.cmds_amount - 1])
		data->ext_val = 127;
}
