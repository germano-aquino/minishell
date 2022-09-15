/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:15:32 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/14 22:55:31 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_conditional_fd(t_minishell *data, t_workspace *vars, int index)
{
	if (data->cmd.files[index].which_input == Infile
		|| data->cmd.files[index].which_input == Heredoc)
		dup42(open(data->cmd.files[index].infile, O_RDONLY),
			vars->fd[index][IN]);
	else if (index == 0 || data->cmd.connector[index - 1] != PIPE)
		dup42(dup(STDIN), vars->fd[index][IN]);
	if (data->cmd.files[index].which_output == Truncate)
		dup42(open(data->cmd.files[index].outfile, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644), vars->fd[index][OUT]);
	else if (data->cmd.files[index].which_output == Append)
		dup42(open(data->cmd.files[index].outfile, \
			O_WRONLY | O_CREAT | O_APPEND, 0644), vars->fd[index][OUT]);
	else if (index == data->cmd.cmds_amount - 1
		|| data->cmd.connector[index] != PIPE)
		dup42(dup(STDOUT), vars->fd[index][OUT]);
}

static void	set_piped_fd(t_minishell *data, t_workspace *vars, int index)
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
	else if (data->cmd.files[index].which_output == Truncate)
		dup42(open(data->cmd.files[index].outfile, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644), vars->fd[index][OUT]);
	else if (data->cmd.files[index].which_output == Append)
		dup42(open(data->cmd.files[index].outfile, \
			O_WRONLY | O_CREAT | O_APPEND, 0644), vars->fd[index][OUT]);
}

static void	set_input_output_fd(t_minishell *data, t_workspace *vars)
{
	int	index;

	index = -1;
	while (++index < data->cmd.cmds_amount)
	{
		if (data->cmd.connector[index] == PIPE
			|| data->cmd.connector[index] == NONE)
			set_piped_fd(data, vars, index);
		else
			set_conditional_fd(data, vars, index);
	}
}

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

void	initialize_workspace(t_minishell *data, t_workspace *vars)
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
	vars->wstatus = (int *)malloc(sizeof(int) * data->cmd.cmds_amount);
	ft_memset(vars->wstatus, -1, (data->cmd.cmds_amount * sizeof(int)));
	build_pipeline(data, vars);
	set_input_output_fd(data, vars);
}
