/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 20:18:10 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/25 15:24:27 by maolivei         ###   ########.fr       */
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

static void	invalid_identifier(
	t_minishell *data, char *key, char *value, t_bool is_child)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	if (is_child)
	{
		ft_memfree((void *) &key);
		ft_memfree((void *) &value);
		exit_free(data, EXIT_FAILURE);
	}
	data->ext_val = EXIT_FAILURE;
}

static void	set_variable(t_minishell *data, int index, t_bool is_child)
{
	char	*key;
	char	*value;
	char	*aux;
	size_t	i;

	i = 0;
	while (data->cmd.args[index][++i])
	{
		key = ft_strdup(data->cmd.args[index][i]);
		value = NULL;
		aux = ft_strchr(data->cmd.args[index][i], '=');
		if (aux)
		{
			value = ft_strdup(aux + 1);
			key[ft_strlen(key) - ft_strlen(aux)] = '\0';
		}
		data->ext_val = EXIT_SUCCESS;
		if (!ft_is_word_str(key))
			invalid_identifier(data, key, value, is_child);
		else
			ht_insert(&data->env, key, value);
		ft_memfree((void *) &key);
		ft_memfree((void *) &value);
	}
}

int	builtin_export(t_minishell *data, int index, t_bool is_child)
{
	if (!data->cmd.args[index][1])
		display_export(&data->env);
	set_variable(data, index, is_child);
	if (is_child)
		exit_free(data, EXIT_SUCCESS);
	return (TRUE);
}
