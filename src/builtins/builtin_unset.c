/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:08:27 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/23 19:15:20 by maolivei         ###   ########.fr       */
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
	if (is_child)
		exit_free(data, EXIT_SUCCESS);
	data->ext_val = EXIT_SUCCESS;
	return (TRUE);
}
