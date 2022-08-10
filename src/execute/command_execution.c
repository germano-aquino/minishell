/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:45:49 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/10 15:29:14 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_pipeline(t_minishell *data, t_workspace *vars)
{
	int	index;

	if (data->cmd.cmds_amount > 1)
	{
		close(vars->fd[0][1]);
		index = -1;
		while (++index < (data->cmd.cmds_amount - 1))
			dup2(vars->fd[index + 1][1], vars->fd[index][1]);
	}
}

void	dup42(int fd_1, int *fd_2)
{
	close(*fd_2);
	*fd_2 = fd_1;
}

void	initialize_pipes_and_pid(t_minishell *data, t_workspace *vars)
{
	int	index;

	index = -1;
	vars->fd = (int **) ft_calloc((data->cmd.cmds_amount + 1), sizeof(int *));
	while (++index < data->cmd.cmds_amount)
	{
		vars->fd[index] = (int *) malloc(sizeof(int) * 2);
		pipe(vars->fd[index]);
	}
	vars->pid = (int *) ft_calloc(data->cmd.cmds_amount, sizeof(int));
	set_input_output_fd(data, vars);
}

void	set_input_output_fd(t_minishell *data, t_workspace *vars)
{
	int	index;

	build_pipeline(data, vars);
	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		if (data->cmd.files[index].which_input == Stdin && index == 0)
			dup42(dup(STDIN), &vars->fd[index][0]);
		else if (data->cmd.files[index].which_input == Infile)
			dup42(open(data->cmd.files[index].infile, O_RDONLY),
				&vars->fd[index][0]);
		else if (data->cmd.files[index].which_input == Heredoc)
			dup42(ft_here_doc(data), &vars->fd[index][0]);
		if (data->cmd.files[index].which_output == Stdout
			&& index == data->cmd.cmds_amount - 1)
			dup42(dup(STDOUT), &vars->fd[index][1]);
		else if (data->cmd.files[index].which_output == Overwrite)
			dup42(open(data->cmd.files[index].outfile,
					O_CREAT | O_WRONLY | O_TRUNC, 0644), &vars->fd[index][1]);
		else if (data->cmd.files[index].which_output == Append)
			dup42(open(data->cmd.files[index].outfile,
					O_CREAT | O_WRONLY | O_APPEND, 0644), &vars->fd[index][1]);
	}
}

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

	trigger_signal(data, NULL, &child_handler);
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

void	exec_cmds(t_minishell *data)
{
	t_workspace	vars;
	int			index;

	initialize_pipes_and_pid(data, &vars);
	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		if (!data->cmd.cmd_path[index])
			command_not_found(data, index);
		else
			exec_cmd(data, &vars, index);
	}
	index = -1;
	while (++index < data->cmd.cmds_amount)
		if (vars.pid[index])
			waitpid(vars.pid[index], &data->ext_val, 0);
	ft_memfree((void *)&vars.pid);
	ft_free_matrix((void *)&vars.fd);
	data->ext_val = WEXITSTATUS(data->ext_val);
	if (!data->cmd.cmd_path[data->cmd.cmds_amount - 1])
		data->ext_val = 127;
}
