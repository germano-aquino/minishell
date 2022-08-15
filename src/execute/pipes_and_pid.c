/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_pid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:15:32 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/15 12:31:25 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_pipeline(t_minishell *data, t_workspace *vars)
{
	int	index;

	if (data->cmd.cmds_amount > 1)
	{
		close(vars->fd[0][OUT]);
		index = -1;
		while (++index < (data->cmd.cmds_amount - 1))
			dup2(vars->fd[index + 1][OUT], vars->fd[index][OUT]);
	}
}

static void	dup42(int fd_1, int fd_2)
{
	dup2(fd_1, fd_2);
	close(fd_1);
}

static void	set_input_output_fd(t_minishell *data, t_workspace *vars)
{
	int	index;

	build_pipeline(data, vars);
	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		if (data->cmd.files[index].which_input == Stdin && index == 0)
			dup42(dup(STDIN), vars->fd[index][IN]);
		else if (data->cmd.files[index].which_input == Infile
			|| data->cmd.files[index].which_input == Heredoc)
			dup42(open(data->cmd.files[index].infile, O_RDONLY),
				vars->fd[index][IN]);
		if (data->cmd.files[index].which_output == Stdout
			&& index == data->cmd.cmds_amount - 1)
			dup42(dup(STDOUT), vars->fd[index][OUT]);
		else if (data->cmd.files[index].which_output == Overwrite)
			dup42(open(data->cmd.files[index].outfile,
					O_WRONLY | O_CREAT | O_TRUNC, 0644), vars->fd[index][OUT]);
		else if (data->cmd.files[index].which_output == Append)
			dup42(open(data->cmd.files[index].outfile,
					O_WRONLY | O_CREAT | O_APPEND, 0644), vars->fd[index][OUT]);
	}
}

void	initialize_pipes_and_pid(t_minishell *data, t_workspace *vars)
{
	int	index;

	vars->fd = (int **)ft_calloc((data->cmd.cmds_amount + 1), sizeof(int *));
	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		vars->fd[index] = (int *)malloc(sizeof(int) * PIPE_SIZE);
		pipe(vars->fd[index]);
	}
	vars->pid = (pid_t *)ft_calloc(data->cmd.cmds_amount, sizeof(pid_t));
	set_input_output_fd(data, vars);
}
