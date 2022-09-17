/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:13:39 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/17 02:15:11 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	has_conditional_error(t_minishell *data, t_workspace *vars, int index)
{
	int	last_valid_status;
	int	cursor;

	cursor = index - 1;
	while (cursor > 0 && vars->wstatus[cursor] == -1)
		--cursor;
	last_valid_status = vars->wstatus[cursor];
	if (data->cmd.connector[index - 1] == AND && last_valid_status != 0)
		return (TRUE);
	if (data->cmd.connector[index - 1] == OR && last_valid_status == 0)
		return (TRUE);
	return (FALSE);
}

void	skip_pipeline(t_minishell *data, t_workspace *vars, int *index)
{
	while (data->cmd.connector[*index] != PIPE \
	&& data->cmd.connector[*index] != NONE)
	{
		if (data->cmd.connector[*index] == AND \
		&& data->cmd.connector[*index - 1] == OR \
		&& vars->depth[*index - 1] == vars->depth[*index])
			break ;
		close(vars->fd[*index][IN]);
		close(vars->fd[*index][OUT]);
		++(*index);
	}
	while (data->cmd.connector[*index] == PIPE)
	{
		close(vars->fd[*index][IN]);
		close(vars->fd[*index][OUT]);
		++(*index);
	}
	close(vars->fd[*index][IN]);
	close(vars->fd[*index][OUT]);
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
