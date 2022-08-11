/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:31:55 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/11 16:32:03 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	print_error_msg(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(msg, STDERR);
	return (TRUE);
}

void	exit_error(t_minishell *data, char *cmd, char *msg, int exit_code)
{
	print_error_msg(cmd, msg);
	exit_free(data, exit_code);
}

t_bool	print_perror_msg(char *cmd, char *perror_msg)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	perror(perror_msg);
	return (TRUE);
}

void	exit_perror(t_minishell *data, char *cmd, char *perr, int exit_code)
{
	print_perror_msg(cmd, perr);
	exit_free(data, exit_code);
}
