/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:34:24 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/23 21:37:19 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_init(t_minishell *data)
{
	int	i;

	i = -1;
	data->input = NULL;
	while (++i < HASH_TABLE_SIZE)
		data->env.item[i] = NULL;
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

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	data;
	char		*buff;
	int			i;

	ft_init(&data);
	populate_env_table(&data.env, envp);
	i = -1;
	while (++i < 1)
	{
		buff = readline("MINISHELL>");
		tokenizer(&data, buff);
		display_input(data.input);
		free_input(&data.input);
		free(buff);
	}
	ht_free(&data.env);
	return (0);
}
