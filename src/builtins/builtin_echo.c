/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:08:57 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 02:48:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	builtin_echo(t_data *data, char **argv, t_bool is_child)
{
	size_t	i;
	t_bool	newline;

	i = 1;
	newline = TRUE;
	if (argv[i] && !ft_strcmp(argv[i], "-n"))
	{
		newline = FALSE;
		++i;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], STDOUT);
		if (argv[i])
			ft_putchar_fd(' ', STDOUT);
	}
	if (newline)
		ft_putendl_fd("", STDOUT);
	ft_free_matrix((void *)&argv);
	set_exit_value(data, is_child, EXIT_SUCCESS);
	return (TRUE);
}
