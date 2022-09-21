/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:31:55 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 15:12:02 by maolivei         ###   ########.fr       */
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

void	print_error_file(t_data *data)
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
