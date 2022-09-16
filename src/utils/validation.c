/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:05:14 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/15 21:31:38 by maolivei         ###   ########.fr       */
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

t_bool	has_path_error(t_minishell *data, t_workspace *vars, char *cmd, int i)
{
	if (!cmd)
	{
		vars->wstatus[i] = EXIT_NOT_FOUND;
		return (print_error_msg(*data->cmd.args[i], "command not found"));
	}
	if (*cmd == -1)
		return (vars->wstatus[i] = EXIT_FAILURE, TRUE);
	if (is_directory(cmd))
	{
		vars->wstatus[i] = EXIT_NOT_EXECUTABLE;
		return (print_error_msg(cmd, "Is a directory"));
	}
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
	{
		vars->wstatus[i] = EXIT_NOT_EXECUTABLE;
		return (print_perror_msg(NULL, cmd));
	}
	if (!is_builtin(cmd) && access(cmd, F_OK) != 0)
	{
		vars->wstatus[i] = EXIT_NOT_FOUND;
		return (print_perror_msg(NULL, cmd));
	}
	return (FALSE);
}
