/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: germano <germano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:34:24 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/17 17:39:48 by germano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_init(t_minishell *data)
{
	data->input = NULL;
	data->env.root = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	data;
	char		*buff;
	int			i;

	ft_init(&data);
	populate_env(&data, envp);
	buff = get_trie_value(data.env.root, "USER");
	ft_printf("USER: %s\n", buff);
	free(buff);
	buff = get_trie_value(data.env.root, "HOME");
	ft_printf("HOME: %s\n", buff);
	free(buff);
	i = -1;
/* 	while (++i < 1)
	{
		buff = readline("MINISHELL>");
		tokenizer(&data, buff);
		display_input(data.input);
		free_input(&data.input);
		free(buff);
	} */
	return (0);
}
