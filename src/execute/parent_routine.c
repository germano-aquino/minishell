/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:32:15 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/22 13:57:11 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_conditional_child(t_program *program)
{
	int		status;
	pid_t	wait_return;

	wait_return = waitpid(program->pid, &status, 0);
	if (WIFEXITED(status))
		set_child_wstatus(program, wait_return, WEXITSTATUS(status));
	else
		handle_dead_child(program, wait_return, status);
}

void	wait_child(t_data *data)
{
	int		status;
	pid_t	wait_return;

	while (data->should_wait)
	{
		wait_return = wait(&status);
		if (wait_return == -1)
			break ;
		if (WIFEXITED(status))
			set_child_wstatus(data->programs, wait_return, WEXITSTATUS(status));
		else
			handle_dead_child(data->programs, wait_return, status);
		--data->should_wait;
	}
	if (data->previous_program)
		g_exit_value = data->previous_program->wstatus;
	else
		g_exit_value = data->programs->wstatus;
}

void	parent_routine(t_data *data, t_program *program)
{
	if (data->previous_program && data->previous_program->connector == PIPE)
	{
		close(data->previous_program->pipe_fd[READ]);
		close(data->previous_program->pipe_fd[WRITE]);
	}
	if (program->connector == AND || program->connector == OR)
		wait_conditional_child(program);
	else
		++data->should_wait;
	data->previous_program = program;
}
