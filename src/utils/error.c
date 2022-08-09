/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:31:55 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/08 20:24:49 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_not_found(t_minishell *data, int index)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(*data->cmd.args[index], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}
