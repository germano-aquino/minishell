/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:17:41 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/16 17:17:46 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_conditional_fd(t_minishell *data, t_workspace *vars, int index)
{
	if (data->cmd.files[index].which_input == IN_INFILE \
	|| data->cmd.files[index].which_input == IN_HEREDOC)
		dup42(open(data->cmd.files[index].infile, O_RDONLY),
			vars->fd[index][IN]);
	else if (index == 0 || data->cmd.connector[index - 1] != PIPE)
		dup42(dup(STDIN), vars->fd[index][IN]);
	if (data->cmd.files[index].which_output == OUT_TRUNC)
		dup42(open(data->cmd.files[index].outfile, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644), vars->fd[index][OUT]);
	else if (data->cmd.files[index].which_output == OUT_APPEND)
		dup42(open(data->cmd.files[index].outfile, \
			O_WRONLY | O_CREAT | O_APPEND, 0644), vars->fd[index][OUT]);
	else if (index == data->cmd.cmds_amount - 1 \
	|| data->cmd.connector[index] != PIPE)
		dup42(dup(STDOUT), vars->fd[index][OUT]);
}

static void	set_piped_fd(t_minishell *data, t_workspace *vars, int index)
{
	if (data->cmd.files[index].which_input == IN_STDIN && index == 0)
		dup42(dup(STDIN), vars->fd[index][IN]);
	else if (data->cmd.files[index].which_input == IN_INFILE \
	|| data->cmd.files[index].which_input == IN_HEREDOC)
		dup42(open(data->cmd.files[index].infile, O_RDONLY),
			vars->fd[index][IN]);
	if (data->cmd.files[index].which_output == OUT_STDOUT \
	&& index == data->cmd.cmds_amount - 1)
		dup42(dup(STDOUT), vars->fd[index][OUT]);
	else if (data->cmd.files[index].which_output == OUT_TRUNC)
		dup42(open(data->cmd.files[index].outfile, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644), vars->fd[index][OUT]);
	else if (data->cmd.files[index].which_output == OUT_APPEND)
		dup42(open(data->cmd.files[index].outfile, \
			O_WRONLY | O_CREAT | O_APPEND, 0644), vars->fd[index][OUT]);
}

void	set_input_output_fd(t_minishell *data, t_workspace *vars)
{
	int	index;

	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		if (data->cmd.connector[index] == PIPE \
		|| data->cmd.connector[index] == NONE)
			set_piped_fd(data, vars, index);
		else
			set_conditional_fd(data, vars, index);
	}
}
