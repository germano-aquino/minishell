/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:45:49 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/21 13:21:35 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_fork(t_data *data, t_program **program)
{
	if (has_conditional_error(data->previous_program))
		return (skip_pipeline(&data->previous_program, program), 1);
	if ((*program)->connector == PIPE)
		pipe((*program)->pipe_fd);
	(*program)->pid = fork();
	if ((*program)->pid == 0)
		child_routine(data, (*program));
	else if ((*program)->pid < 0)
		return (0);
	else
		parent_routine(data, (*program));
	return (0);
}

void	execute(t_data *data, t_program *root)
{
	if (!root)
		return ;
	trigger_signal(FALSE, cmd_handler);
	if (!root->right && root->type == NORMAL && is_builtin(root->path))
	{
		exec_builtin(data, root, FALSE);
		return ;
	}
	while (root)
	{
		if (create_fork(data, &root) != 0)
			continue ;
		root = root->right;
	}
	wait_child(data);
}
