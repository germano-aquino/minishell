/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:57:22 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/06 22:19:23 by grenato-         ###   ########.fr       */
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

int		get_ht_items_amount(t_hash_table *table)
{
	int	i;
	int	items_amount;
	t_hnode *tmp;

	i = -1;
	items_amount = 0;
	while (++i < HASH_TABLE_SIZE)
	{
		if (table->item[i] != NULL)
		{
			items_amount++;
			tmp = table->item[i]->next;
			while (tmp != NULL)
			{
				items_amount++;
				tmp = tmp->next;
			}
		}
	}
	return (items_amount);
}

char	*get_key_value_from_item(t_hnode *item)
{
	char	*key_value;

	key_value = ft_strdup(item->key);
	key_value = join_str_and_free(key_value, ft_strjoin("=", item->value));
	return (key_value);
}

char	**get_env_from_ht(t_hash_table *table)
{
	int		i;
	int		j;
	int		nb_of_vars;
	char	**env;
	t_hnode	*tmp;

	nb_of_vars = get_ht_items_amount(table);
	env = (char **)malloc(sizeof(char *) * (nb_of_vars + 1));
	i = -1;
	j = 0;
	while (++i < HASH_TABLE_SIZE)
	{
		if (table->item[i] != NULL)
		{
			env[j++] = get_key_value_from_item(table->item[i]);
			tmp = table->item[i]->next;
			while (tmp != NULL)
			{
				env[j++] = get_key_value_from_item(tmp);
				tmp = tmp->next;
			}
		}
	}
	env[j] = NULL;
	return (env);
}
