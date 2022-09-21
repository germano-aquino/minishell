/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:05:14 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 03:26:28 by maolivei         ###   ########.fr       */
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

t_bool	has_path_error(t_program *program)
{
	if (!program->args)
		return (FALSE);
	if (!program->path)
	{
		program->wstatus = EXIT_NOT_FOUND;
		return (print_error_msg((char *)program->args->content,
				"command not found"));
	}
	if (is_directory(program->path))
	{
		program->wstatus = EXIT_NOT_EXECUTABLE;
		return (print_error_msg(program->path, "Is a directory"));
	}
	if (access(program->path, F_OK) == 0 && access(program->path, X_OK) != 0)
	{
		program->wstatus = EXIT_NOT_EXECUTABLE;
		return (print_perror_msg(NULL, program->path));
	}
	if (!is_builtin(program->path) && access(program->path, F_OK) != 0)
	{
		program->wstatus = EXIT_NOT_FOUND;
		return (print_perror_msg(NULL, program->path));
	}
	return (FALSE);
}
