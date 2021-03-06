/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:57:18 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/23 21:29:46 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	insert_colliding_item(t_hnode *curr_item, char *key, char *value)
{
	while (curr_item->next != NULL)
	{
		curr_item = curr_item->next;
		if (!ft_strncmp(key, curr_item->key, max_size(key, curr_item->key)))
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
	if (curr_item == NULL)
		table->item[index] = create_item(key, value);
	else if (!ft_strncmp(key, curr_item->key, max_size(key, curr_item->key)))
	{
		free(curr_item->value);
		curr_item->value = ft_strdup(value);
	}
	else
		insert_colliding_item(curr_item, key, value);
}

char	*ht_search(t_hash_table *table, char *key)
{
	int		index;
	t_hnode	*curr_item;

	index = hash_function(key);
	curr_item = table->item[index];
	while (curr_item != NULL)
	{
		if (!ft_strncmp(key, curr_item->key, max_size(key, curr_item->key)))
			return (curr_item->value);
		curr_item = curr_item->next;
	}
	return (NULL);
}

void	delete_colliding_item(t_hnode *item, char *key)
{
	t_hnode	*previous;

	previous = NULL;
	while (item != NULL && ft_strncmp(key, item->key, max_size(key, item->key)))
	{
		previous = item;
		item = item->next;
	}
	if (item == NULL)
		return ;
	else if (item->next == NULL)
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
	if (!ft_strncmp(key, item->key, max_size(key, item->key)))
	{
		table->item[index] = item->next;
		item->next = NULL;
		free_item(item);
	}
	else
		delete_colliding_item(item, key);
}
