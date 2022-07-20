/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:31:55 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/20 19:58:29 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_not_found(t_minishell *data, t_workspace *vars)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(*data->cmd.args[vars->i], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}
