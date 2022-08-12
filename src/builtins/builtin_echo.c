/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:08:57 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/12 13:32:21 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_minishell *data, int index, t_bool is_child)
{
	size_t	i;
	t_bool	newline;

	i = 1;
	newline = TRUE;
	if (data->cmd.args[index][i] && !ft_strcmp(data->cmd.args[index][i], "-n"))
	{
		newline = FALSE;
		++i;
	}
	while (data->cmd.args[index][i])
	{
		ft_putstr_fd(data->cmd.args[index][i++], STDOUT);
		if (data->cmd.args[index][i])
			ft_putchar_fd(' ', STDOUT);
	}
	if (newline)
		ft_putendl_fd("", STDOUT);
	set_exit_value(data, is_child, EXIT_SUCCESS);
	return (TRUE);
}
