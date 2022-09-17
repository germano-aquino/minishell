/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:15:32 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/17 02:18:19 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	match_depth_fd(t_minishell *data, t_workspace *vars, int current_index)
{
	int	depth;
	int	index;
	int	last_of_depth;

	index = current_index;
	while (index < data->cmd.cmds_amount && vars->depth[index] == 1)
		++index;
	if (index >= data->cmd.cmds_amount)
		return ;
	depth = vars->depth[index];
	last_of_depth = index;
	while (last_of_depth < data->cmd.cmds_amount - 1 \
	&& vars->depth[last_of_depth + 1] == depth)
		++last_of_depth;
	while (index < last_of_depth)
	{
		if (data->cmd.connector[index] != PIPE)
			dup2(vars->fd[last_of_depth][OUT], vars->fd[index][OUT]);
		++index;
	}
	if (last_of_depth < data->cmd.cmds_amount)
		match_depth_fd(data, vars, last_of_depth + 1);
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
	vars->depth = (int *)malloc(sizeof(int) * (data->cmd.cmds_amount + 1));
	index = -1;
	while (++index < data->cmd.cmds_amount + 1)
		vars->depth[index] = data->cmd.depth[index];
	vars->pid = (pid_t *)ft_calloc(data->cmd.cmds_amount, sizeof(pid_t));
	vars->wstatus = (int *)malloc(sizeof(int) * data->cmd.cmds_amount);
	ft_memset(vars->wstatus, -1, (data->cmd.cmds_amount * sizeof(int)));
	build_pipeline(data, vars);
	set_input_output_fd(data, vars);
	match_depth_fd(data, vars, 0);
}
