/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:57:18 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/31 13:37:50 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_colliding_item(t_hnode *curr_item, char *key, char *value)
{
	while (curr_item->next)
	{
		curr_item = curr_item->next;
		if (ft_strcmp(key, curr_item->key) == 0)
		{
			free(curr_item->value);
			curr_item->value = ft_strdup(value);
			return ;
		}
	}
	curr_item->next = create_item(key, value);
}

void	ht_insert(t_hash_table *table, char *key, char *value)
{
	int		index;
	t_hnode	*curr_item;

	index = hash_function(key);
	curr_item = table->item[index];
	if (!curr_item)
		table->item[index] = create_item(key, value);
	else if (ft_strcmp(key, curr_item->key) == 0)
	{
		if (value)
		{
			free(curr_item->value);
			curr_item->value = ft_strdup(value);
		}
	}
	else
		insert_colliding_item(curr_item, key, value);
}

static void	delete_colliding_item(t_hnode *item, char *key)
{
	t_hnode	*previous;

	previous = NULL;
	while (item && ft_strcmp(key, item->key))
	{
		previous = item;
		item = item->next;
	}
	if (!item)
		return ;
	else if (!item->next)
	{
		previous->next = NULL;
		free_item(item);
	}
	else
	{
		previous->next = item->next;
		item->next = NULL;
		free_item(item);
	}
}

void	ht_delete(t_hash_table *table, char *key)
{
	int		index;
	t_hnode	*item;

	index = hash_function(key);
	item = table->item[index];
	if (item)
	{
		if (ft_strcmp(key, item->key) == 0)
		{
			table->item[index] = item->next;
			item->next = NULL;
			free_item(item);
		}
		else
			delete_colliding_item(item, key);
	}
}

char	*ht_search(t_hash_table *table, char *key)
{
	int		index;
	t_hnode	*curr_item;

	index = hash_function(key);
	curr_item = table->item[index];
	while (curr_item)
	{
		if (ft_strcmp(key, curr_item->key) == 0)
			return (curr_item->value);
		curr_item = curr_item->next;
	}
	return (NULL);
}
