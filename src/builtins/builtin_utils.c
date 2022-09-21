/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:07:33 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 02:48:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_value(t_data *data, t_bool is_child, int exit_code)
{
	if (is_child)
		exit_free(data, exit_code);
	g_exit_value = exit_code;
}

t_bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	return (ft_strcmp(cmd, "exit") == 0 \
	|| ft_strcmp(cmd, "echo") == 0 \
	|| ft_strcmp(cmd, "env") == 0 \
	|| ft_strcmp(cmd, "unset") == 0 \
	|| ft_strcmp(cmd, "pwd") == 0 \
	|| ft_strcmp(cmd, "cd") == 0 \
	|| ft_strcmp(cmd, "export") == 0);
}
