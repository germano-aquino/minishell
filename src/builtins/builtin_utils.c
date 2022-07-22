/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:07:33 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/22 15:28:31 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_number_str(const char *str)
{
	size_t	index;

	index = 0;
	if (str[index] == '-' || str[index] == '+')
		++index;
	while (str[index])
		if (!ft_isdigit(str[index++]))
			return (FALSE);
	return (TRUE);
}

int	check_builtin(t_minishell *data, int index, t_bool is_child)
{
	if (ft_strcmp(*data->cmd.args[index], "exit") == 0)
		return (builtin_exit(data, index, is_child));
	else if (ft_strcmp(*data->cmd.args[index], "echo") == 0)
		return (builtin_echo(data, index, is_child));
	return (FALSE);
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0);
}
