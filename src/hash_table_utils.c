/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:57:22 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/04 23:56:56 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	hash_function(char *key)
{
	unsigned int	tmp;
	__uint32_t		hash;

	hash = 0;
	while (*key != '\0')
	{
		hash = (hash << 4) + (*key);
		tmp = hash & 0xf0000000;
		if (tmp)
		{
			hash ^= tmp >> 24;
			hash ^= tmp;
		}
		key++;
	}
	return ((int)(hash % HASH_TABLE_SIZE));
}

t_hnode	*create_item(char *key, char *value)
{
	t_hnode	*item;

	item = (t_hnode *)malloc(sizeof(t_hnode));
	item->key = ft_strdup(key);
	item->value = ft_strdup(value);
	item->next = NULL;
	return (item);
}

void	free_item(t_hnode *item)
{
	t_hnode	*temp;

	while (item != NULL)
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
		if (temp != NULL)
			free_item(temp);
	}
}
