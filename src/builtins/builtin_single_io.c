/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_single_io.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:07:09 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/12 15:06:47 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_io_builtin(t_workspace *vars, int *std_io)
{
	dup2(std_io[IN], STDIN);
	dup2(std_io[OUT], STDOUT);
	close(std_io[IN]);
	close(std_io[OUT]);
	ft_memfree((void *)&vars->pid);
	ft_free_matrix((void *)&vars->fd);
}

void	set_io_builtin(t_minishell *data, t_workspace *vars, int *std_io)
{
	std_io[IN] = dup(STDIN);
	std_io[OUT] = dup(STDOUT);
	initialize_pipes_and_pid(data, vars);
	dup2(vars->fd[0][IN], STDIN);
	dup2(vars->fd[0][OUT], STDOUT);
	close(vars->fd[0][IN]);
	close(vars->fd[0][OUT]);
}
