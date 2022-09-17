/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:54:45 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/17 01:53:32 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

static void	display_env(t_hash_table *table)
{
	size_t	index;
	t_hnode	*item;

	index = 0;
	while (index < HASH_TABLE_SIZE)
	{
		item = table->item[index];
		while (item)
		{
			if (item->value)
				printf("%s=%s\n", item->key, item->value);
			item = item->next;
		}
		++index;
	}
}

t_bool	builtin_env(t_minishell *data, t_bool is_child)
{
	display_env(&data->env);
	set_exit_value(data, is_child, EXIT_SUCCESS);
	return (TRUE);
}
