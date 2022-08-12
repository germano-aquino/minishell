/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_pid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:15:32 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/11 22:05:44 by grenato-         ###   ########.fr       */
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

void	dup42(int fd_1, int fd_2)
{
	dup2(fd_1, fd_2);
	close(fd_1);
}

void	set_input_output_fd(t_minishell *data, t_workspace *vars)
{
	int	index;

	build_pipeline(data, vars);
	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		if (data->cmd.files[index].which_input == Stdin && index == 0)
			dup42(dup(STDIN), vars->fd[index][0]);
		else if (data->cmd.files[index].which_input == Infile
			|| data->cmd.files[index].which_input == Heredoc)
			dup42(open(data->cmd.files[index].infile, O_RDONLY),
				vars->fd[index][0]);
		if (data->cmd.files[index].which_output == Stdout
			&& index == data->cmd.cmds_amount - 1)
			dup42(dup(STDOUT), vars->fd[index][1]);
		else if (data->cmd.files[index].which_output == Overwrite)
			dup42(open(data->cmd.files[index].outfile,
					O_CREAT | O_WRONLY | O_TRUNC, 0644), vars->fd[index][1]);
		else if (data->cmd.files[index].which_output == Append)
			dup42(open(data->cmd.files[index].outfile,
					O_CREAT | O_WRONLY | O_APPEND, 0644), vars->fd[index][1]);
	}
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
