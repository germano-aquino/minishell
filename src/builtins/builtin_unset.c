/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:08:27 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/26 20:55:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_minishell *data, int index, t_bool is_child)
{
	size_t	i;

	i = 0;
	while (data->cmd.args[index][i])
	{
		ht_delete(&data->env, data->cmd.args[index][i]);
		++i;
	}
	set_exit_value(data, is_child, EXIT_SUCCESS);
	return (TRUE);
}
