/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:17:18 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/22 13:39:05 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_minishell(t_data *data)
{
	int	i;

	i = -1;
	while (++i < HASH_TABLE_SIZE)
		data->env.item[i] = NULL;
	data->input = NULL;
	data->programs = NULL;
	data->previous_program = NULL;
	data->should_wait = 0;
}
