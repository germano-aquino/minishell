/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_wstatus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:19:21 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 04:03:44 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_child_wstatus(t_program *program, pid_t process_id, int status)
{
	if (!program)
		return ;
	if (program->pid == process_id)
	{
		program->wstatus = status;
		return ;
	}
	set_child_wstatus(program->right, process_id, status);
	set_child_wstatus(program->left, process_id, status);
}
