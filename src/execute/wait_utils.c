/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:13:39 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/19 13:06:10 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	has_conditional_error(t_minishell *data, t_workspace *vars, int index)
{
	if (data->cmd.connector[index - 1] == AND && vars->wstatus[index - 1] != 0)
		return (TRUE);
	if (data->cmd.connector[index - 1] == OR && vars->wstatus[index - 1] == 0)
		return (TRUE);
	return (FALSE);
}

void	skip_matching_depth(t_workspace *vars, int *index, int current_depth)
{
	while (vars->depth[*index] == current_depth)
	{
		vars->wstatus[*index] = vars->wstatus[*index - 1];
		close(vars->fd[*index][IN]);
		close(vars->fd[*index][OUT]);
		++(*index);
	}
	--(*index);
}

void	skip_pipeline(t_minishell *data, t_workspace *vars, int *index)
{
	const int	previous_depth = vars->depth[*index - 1];
	const int	current_depth = vars->depth[*index];

	while (data->cmd.connector[*index] == PIPE)
	{
		vars->wstatus[*index] = vars->wstatus[*index - 1];
		close(vars->fd[*index][IN]);
		close(vars->fd[*index][OUT]);
		++(*index);
	}
	if (previous_depth != current_depth)
		skip_matching_depth(vars, index, current_depth);
	else
	{
		vars->wstatus[*index] = vars->wstatus[*index - 1];
		close(vars->fd[*index][IN]);
		close(vars->fd[*index][OUT]);
	}
}

void	wait_conditional_child(t_workspace *vars, int index)
{
	int		status;
	pid_t	wait_return;

	if (vars->pid[index])
	{
		wait_return = waitpid(vars->pid[index], &status, 0);
		if (WIFEXITED(status))
			set_child_wstatus(vars, wait_return, WEXITSTATUS(status));
		else
			handle_dead_child(vars, wait_return, status);
	}
}

void	wait_child(t_workspace *vars, int cmds_amount, int should_wait)
{
	int		index;
	int		status;
	pid_t	wait_return;

	index = -1;
	while (++index < should_wait)
	{
		wait_return = wait(&status);
		if (wait_return == -1)
			break ;
		if (WIFEXITED(status))
			set_child_wstatus(vars, wait_return, WEXITSTATUS(status));
		else
			handle_dead_child(vars, wait_return, status);
	}
	while (vars->wstatus[cmds_amount - 1] == -1)
		--cmds_amount;
	g_exit_value = vars->wstatus[cmds_amount - 1];
}
