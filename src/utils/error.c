/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:31:55 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/22 13:39:48 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	print_error_msg(char *cmd, char *msg)
{
	char	*output;

	output = ft_strdup("minishell: ");
	if (cmd)
	{
		output = ft_strjoin_free(output, ft_strdup(cmd));
		output = ft_strjoin_free(output, ft_strdup(": "));
	}
	output = ft_strjoin_free(output, ft_strdup(msg));
	ft_putendl_fd(output, STDERR);
	free(output);
	return (TRUE);
}

t_bool	print_perror_msg(char *cmd, char *perror_msg)
{
	char	*output;

	output = ft_strdup("minishell: ");
	if (cmd)
	{
		output = ft_strjoin_free(output, ft_strdup(cmd));
		output = ft_strjoin_free(output, ft_strdup(": "));
	}
	output = ft_strjoin_free(output, ft_strdup(perror_msg));
	output = ft_strjoin_free(output, ft_strdup(": "));
	output = ft_strjoin_free(output, ft_strdup(strerror(errno)));
	ft_putendl_fd(output, STDERR);
	free(output);
	return (TRUE);
}

void	exit_perror(t_data *data, char *cmd, char *perr, int exit_code)
{
	print_perror_msg(cmd, perr);
	exit_free(data, exit_code);
}
