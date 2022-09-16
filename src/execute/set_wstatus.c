/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wstatus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:19:21 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/16 16:34:28 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	match_depth_status(t_workspace *vars, int status, int index)
{
	int	depth;

	depth = vars->depth[index];
	if (depth == 1)
		return ;
	while (vars->depth[++index] == depth)
		vars->wstatus[index] = status;
}

void	set_child_wstatus(t_workspace *vars, pid_t process_id, int status)
{
	size_t	index;

	index = 0;
	while (vars->pid[index] != process_id)
		++index;
	vars->wstatus[index] = status;
	match_depth_status(vars, status, index);
}
