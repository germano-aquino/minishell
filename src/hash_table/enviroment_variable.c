/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 00:29:27 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/22 21:33:13 by maolivei         ###   ########.fr       */
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

void	populate_env_table(t_hash_table *table, char *envp[])
{
	char	**key_value;
	int		i;

	i = -1;
	while (envp[++i] != NULL)
	{
		key_value = ft_split(envp[i], '=');
		ht_insert(table, key_value[0], key_value[1]);
		ft_free_2d_char_ptr(&key_value);
	}
}

static char	*get_key_value_from_item(t_hnode *item)
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
	char	**env;
	t_hnode	*tmp;

	env = (char **)malloc(sizeof(char *) * (get_ht_size(table) + 1));
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
