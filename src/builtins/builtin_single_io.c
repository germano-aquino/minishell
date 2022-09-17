/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_single_io.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:07:09 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/17 01:58:36 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_io_builtin(t_workspace *vars, int *std_io)
{
	dup42(std_io[IN], STDIN);
	dup42(std_io[OUT], STDOUT);
	free_workspace(vars);
}

void	set_io_builtin(t_minishell *data, t_workspace *vars, int *std_io)
{
	std_io[IN] = dup(STDIN);
	std_io[OUT] = dup(STDOUT);
	initialize_workspace(data, vars);
	dup42(vars->fd[0][IN], STDIN);
	dup42(vars->fd[0][OUT], STDOUT);
}
