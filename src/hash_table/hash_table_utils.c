/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:57:22 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 15:26:30 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hash_function(char *key)
{
	unsigned int	tmp;
	__uint32_t		hash;

	hash = 0;
	while (*key)
	{
		hash = (hash << HASH_LEFT_OFFSET) + (*key);
		tmp = hash & HASH_LIMITER;
		if (tmp)
		{
			hash ^= tmp >> HASH_RIGHT_OFFSET;
			hash ^= tmp;
		}
		key++;
	}
	return ((int)(hash % HASH_TABLE_SIZE));
}

t_hnode	*create_item(char *key, char *value)
{
	t_hnode	*item;

	item = (t_hnode *)ft_calloc(1, sizeof(t_hnode));
	if (key)
		item->key = ft_strdup(key);
	if (value)
		item->value = ft_strdup(value);
	return (item);
}

void	free_item(t_hnode *item)
{
	t_hnode	*temp;

	while (item)
	{
		temp = item;
		item = item->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	ht_free(t_hash_table *table)
{
	int		i;
	t_hnode	*temp;

	i = -1;
	while (++i < HASH_TABLE_SIZE)
	{
		temp = table->item[i];
		if (temp)
			free_item(temp);
	}
}
