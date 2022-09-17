/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:17:41 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/17 02:04:22 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_output_files(t_minishell *data, t_workspace *vars, int i)
{
	const t_output	current_output = data->cmd.files[i].which_output;
	const char		*file_out = data->cmd.files[i].outfile;
	int				outfile_fd;

	if (current_output == OUT_STDOUT \
	&& (i == data->cmd.cmds_amount - 1 || data->cmd.connector[i] != PIPE))
		outfile_fd = dup(STDOUT);
	else if (current_output == OUT_TRUNC)
		outfile_fd = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (current_output == OUT_APPEND)
		outfile_fd = open(file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return ;
	dup42(outfile_fd, vars->fd[i][OUT]);
}

static void	set_input_files(t_minishell *data, t_workspace *vars, int i)
{
	const t_input	current_input = data->cmd.files[i].which_input;
	const char		*file_in = data->cmd.files[i].infile;
	int				infile_fd;

	if (current_input == IN_STDIN \
	&& (i == 0 || data->cmd.connector[i - 1] != PIPE))
		infile_fd = dup(STDIN);
	else if (current_input == IN_INFILE || current_input == IN_HEREDOC)
		infile_fd = open(file_in, O_RDONLY);
	else
		return ;
	dup42(infile_fd, vars->fd[i][IN]);
}

void	set_input_output_fd(t_minishell *data, t_workspace *vars)
{
	int	index;

	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		set_input_files(data, vars, index);
		set_output_files(data, vars, index);
	}
}
