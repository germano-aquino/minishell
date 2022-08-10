/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_single_io.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:07:09 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/10 17:12:54 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_io_builtin(t_workspace *vars, int *std_io)
{
	dup2(std_io[0], STDIN);
	dup2(std_io[1], STDOUT);
	close(std_io[0]);
	close(std_io[1]);
	ft_memfree((void *)&vars->pid);
	ft_free_matrix((void *)&vars->fd);
}

void	set_io_builtin(t_minishell *data, t_workspace *vars, int *std_io)
{
	std_io[0] = dup(STDIN);
	std_io[1] = dup(STDOUT);
	initialize_pipes_and_pid(data, vars);
	dup2(vars->fd[0][0], STDIN);
	dup2(vars->fd[0][1], STDOUT);
	close(vars->fd[0][0]);
	close(vars->fd[0][1]);
}
