/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:31:55 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/23 03:55:45 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	print_error_msg(char *cmd, char *msg)
{
	if (cmd)
		ft_dprintf(STDERR, "minishell: %s: %s\n", cmd, msg);
	else
		ft_dprintf(STDERR, "minishell: %s\n", msg);
	return (TRUE);
}

t_bool	print_perror_msg(char *cmd, char *perror_msg)
{
	if (cmd)
		ft_dprintf(STDERR, "minishell: %s: %s: %s\n", cmd, perror_msg, \
		strerror(errno));
	else
		ft_dprintf(STDERR, "minishell: %s: %s\n", perror_msg, \
		strerror(errno));
	return (TRUE);
}

void	exit_perror(t_data *data, char *cmd, char *perr, int exit_code)
{
	print_perror_msg(cmd, perr);
	exit_free(data, exit_code);
}
