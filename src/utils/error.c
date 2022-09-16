/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:31:55 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/16 14:58:50 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	print_error_msg(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putendl_fd(msg, STDERR);
	return (TRUE);
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

void	print_error_file(t_minishell *data)
{
	char	*line;
	int		fd;

	fd = open(TMP_ERROR_PATH, O_RDONLY);
	line = ft_gnl(fd);
	while (line != NULL)
	{
		ft_putstr_fd(line, data->fd_err);
		ft_memfree((void *) &line);
		line = ft_gnl(fd);
	}
	close(fd);
}
