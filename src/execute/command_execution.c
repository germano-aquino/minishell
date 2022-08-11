/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:45:49 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/11 20:41:36 by grenato-         ###   ########.fr       */
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

void	exec_cmd(t_minishell *data, t_workspace *vars, int index)
{
	char	**envp;
	int		i;

	vars->pid[index] = fork();
	if (vars->pid[index] == 0)
	{
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
	else
	{
		close(vars->fd[index][0]);
		close(vars->fd[index][1]);
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
		g_ext_val = WEXITSTATUS(data->child_exit_code);
	if (!data->cmd.cmd_path[data->cmd.cmds_amount - 1])
		g_ext_val = 127;
}

void	exec_cmds(t_minishell *data)
{
	t_workspace	vars;
	int			index;

	if (!*data->cmd.args)
		return ;
	trigger_signal(0, &cmd_handler);
	initialize_pipes_and_pid(data, &vars);
	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		if (!*data->cmd.cmd_path[index])
		{
			close(vars.fd[index][0]);
			close(vars.fd[index][1]);
			if (g_ext_val == EXIT_SUCCESS)
				g_ext_val = EXIT_FAILURE;
		}
		else
			exec_cmd(data, &vars, index);
	}
	wait_child(data, &vars);
	ft_memfree((void *)&vars.pid);
	ft_free_matrix((void *)&vars.fd);
}
