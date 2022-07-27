/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:45:49 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/26 19:58:40 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_input_output_fd(t_minishell *data)
{
	if (data->files.which_input == Stdin)
		data->fd[0] = dup(STDIN_FILENO);
	else if (data->files.which_input == Infile)
		data->fd[0] = open(data->files.infile, O_RDONLY);
	else if (data->files.which_input == Heredoc)
		data->fd[0] = ft_here_doc(data);
	if (data->files.which_output == Stdout)
		data->fd[1] = dup(STDOUT_FILENO);
	else if (data->files.which_output == Overwrite)
		data->fd[1] = open(
				data->files.outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		data->fd[1] = open(
				data->files.outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	data->files.which_input = Stdin;
	data->files.which_output = Stdout;
}

void	call_execve_or_builtin(
	t_minishell *data, t_workspace *vars, char **envp)
{
	free(vars->pid);
	if (!is_builtin(data->cmd.cmd_path[vars->i]))
	{
		if (execve(data->cmd.cmd_path[vars->i],
				data->cmd.args[vars->i], envp) == -1)
		{
			ft_free_matrix((void *) &envp);
			perror("minishell: execve");
			exit_free(data, EXIT_FAILURE);
		}
	}
	ft_free_matrix((void *) &envp);
	check_builtin(data, vars->i, TRUE);
}

void	child_task(t_minishell *data, t_workspace *vars)
{
	char	**envp;

	trigger_signal(data, NULL, &child_handler);
	envp = get_env_from_ht(&data->env);
	dup2(vars->curr_fd, STDIN_FILENO);
	if (vars->i == data->cmd.cmds_amount - 1)
		dup2(data->fd[1], STDOUT_FILENO);
	else
		dup2(vars->fd[1], STDOUT_FILENO);
	close(vars->curr_fd);
	close(vars->fd[0]);
	close(vars->fd[1]);
	close(data->fd[1]);
	call_execve_or_builtin(data, vars, envp);
}

void	exec_cmd(t_minishell *data, t_workspace *vars)
{
	if (pipe(vars->fd) == -1)
		ft_exit(data, "cannot create pipe.\n", NULL, 0);
	if (vars->curr_fd == -1)
		vars->curr_fd = vars->fd[0];
	vars->pid[vars->i] = fork();
	if (vars->pid[vars->i] == 0)
		child_task(data, vars);
	else
	{
		close(vars->curr_fd);
		dup2(vars->fd[0], vars->curr_fd);
		close(vars->fd[0]);
		close(vars->fd[1]);
	}
}

void	exec_cmds(t_minishell *data)
{
	t_workspace	vars;

	vars.i = -1;
	set_input_output_fd(data);
	vars.curr_fd = data->fd[0];
	vars.pid = (int *) ft_calloc(data->cmd.cmds_amount, sizeof(int));
	while (++vars.i < data->cmd.cmds_amount)
	{
		if (!data->cmd.cmd_path[vars.i])
			command_not_found(data, &vars);
		else if (!(vars.i == (data->cmd.cmds_amount - 1) && data->fd[1] == -1))
			exec_cmd(data, &vars);
	}
	vars.i = -1;
	while (++vars.i < data->cmd.cmds_amount)
		if (vars.pid[vars.i])
			waitpid(vars.pid[vars.i], &data->ext_val, 0);
	close(vars.curr_fd);
	close(data->fd[1]);
	free(vars.pid);
	data->ext_val = WEXITSTATUS(data->ext_val);
	if (!data->cmd.cmd_path[data->cmd.cmds_amount - 1])
		data->ext_val = 127;
}
