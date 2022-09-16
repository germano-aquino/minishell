/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_single_io.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:07:09 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/16 16:10:25 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_io_builtin(t_workspace *vars, int *std_io)
{
	dup42(std_io[IN], STDIN);
	dup42(std_io[OUT], STDOUT);
	ft_memfree((void *)&vars->pid);
	ft_memfree((void *)&vars->depth);
	ft_memfree((void *)&vars->wstatus);
	ft_free_matrix((void *)&vars->fd);
}

void	set_io_builtin(t_minishell *data, t_workspace *vars, int *std_io)
{
	std_io[IN] = dup(STDIN);
	std_io[OUT] = dup(STDOUT);
	initialize_workspace(data, vars);
	dup42(vars->fd[0][IN], STDIN);
	dup42(vars->fd[0][OUT], STDOUT);
}
