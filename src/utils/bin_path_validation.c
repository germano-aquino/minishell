/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:05:14 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/08 15:30:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_path(char *str)
{
	return (!!ft_strchr(str, '/'));
}

t_bool	is_directory(char *path)
{
	t_stat	stat_buf;

	if (stat(path, &stat_buf) != 0)
		return (FALSE);
	if (S_ISDIR(stat_buf.st_mode))
		if (is_path(path))
			return (TRUE);
	return (FALSE);
}

t_bool	validate_path(t_minishell *data, char *path, int cmd_pos)
{
	if (!path)
	{
		g_exit_value = EXIT_NOT_FOUND;
		return (print_error_msg(*data->cmd.args[cmd_pos], "command not found"));
	}
	if (*path == -1)
		return (TRUE);
	if (is_directory(path))
	{
		g_exit_value = EXIT_NOT_EXECUTABLE;
		return (print_error_msg(path, "Is a directory"));
	}
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		g_exit_value = EXIT_NOT_EXECUTABLE;
		return (print_perror_msg(NULL, path));
	}
	if (!is_builtin(path) && access(path, F_OK) != 0)
	{
		g_exit_value = EXIT_NOT_FOUND;
		return (print_perror_msg(NULL, path));
	}
	return (FALSE);
}
