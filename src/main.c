/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:34:24 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/29 01:30:25 by grenato-         ###   ########.fr       */
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

void	display_cmd_table(t_command_table *cmd)
{
	int	cmd_pos;
	int	i;

	cmd_pos = -1;
	while(cmd->cmd_path[++cmd_pos] != NULL)
	{
		ft_printf("cmd_path: %s\n", cmd->cmd_path[cmd_pos]);
		i = -1;
		while (cmd->args[cmd_pos][++i] != NULL)
			ft_printf("args: %s\n\n", cmd->args[cmd_pos][i]);
	}
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
		lexer(&data);
		display_input(data.input);
		display_cmd_table(&data.cmd);
		free_input(&data.input);
		free(buff);
	}
	ht_free(&data.env);
	return (0);
}
