/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_from_ht.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:23:17 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/13 14:23:22 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_ht_size(t_hash_table *table)
{
	int		i;
	int		items_amount;
	t_hnode	*tmp;

	i = -1;
	items_amount = 0;
	while (++i < HASH_TABLE_SIZE)
	{
		if (table->item[i])
		{
			items_amount++;
			tmp = table->item[i]->next;
			while (tmp)
			{
				items_amount++;
				tmp = tmp->next;
			}
		}
	}
	return (items_amount);
}

static char	*get_key_value_from_item(t_hnode *item)
{
	char	*key_value;

	key_value = ft_strdup(item->key);
	key_value = join_free(key_value, ft_strjoin("=", item->value));
	return (key_value);
}

char	**get_env_from_ht(t_hash_table *table)
{
	int		i;
	int		j;
	char	**env;
	t_hnode	*tmp;

	env = (char **)malloc(sizeof(char *) * (get_ht_size(table) + 1));
	i = -1;
	j = 0;
	while (++i < HASH_TABLE_SIZE)
	{
		if (table->item[i])
		{
			env[j++] = get_key_value_from_item(table->item[i]);
			tmp = table->item[i]->next;
			while (tmp)
			{
				env[j++] = get_key_value_from_item(tmp);
				tmp = tmp->next;
			}
		}
	}
	env[j] = NULL;
	return (env);
}
