/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:18:10 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/23 03:46:05 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_export(t_hash_table *table)
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
				printf("declare -x %s=\"%s\"\n", item->key, item->value);
			else
				printf("declare -x %s\n", item->key);
			item = item->next;
		}
		++index;
	}
}

static void	invalid_identifier(char *key)
{
	ft_dprintf(STDERR, "minishell: export `%s': not a valid identifier\n", key);
	g_exit_value = EXIT_FAILURE;
}

static void	set_variable(t_data *data, char **argv)
{
	char	*key;
	char	*value;
	char	*aux;
	size_t	i;

	i = 0;
	while (argv[++i])
	{
		key = ft_strdup(argv[i]);
		value = NULL;
		aux = ft_strchr(argv[i], '=');
		if (aux)
		{
			value = ft_strdup(aux + 1);
			key[ft_strlen(key) - ft_strlen(aux)] = '\0';
		}
		g_exit_value = EXIT_SUCCESS;
		if (!is_word_str(key))
			invalid_identifier(key);
		else
			ht_insert(&data->env, key, value);
		ft_memfree((void *)&key);
		ft_memfree((void *)&value);
	}
}

t_bool	builtin_export(t_data *data, char **argv, t_bool is_child)
{
	if (!argv[1])
		display_export(&data->env);
	set_variable(data, argv);
	ft_free_matrix((void *)&argv);
	if (is_child)
		exit_free(data, g_exit_value);
	return (TRUE);
}
