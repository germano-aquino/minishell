/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:31:55 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/20 15:32:03 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_not_found(t_minishell *data)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(*data->cmd.args[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit_free(data, 127);
}
