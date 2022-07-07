/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:34:24 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/06 22:39:28 by grenato-         ###   ########.fr       */
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
	data->cmd.cmds_amount = 0;
	data->cmd.cmd_path = NULL;
	data->cmd.args = NULL;
	data->ext_val = 0;
	data->fd[0] = 0;
	data->fd[1] = 1;
	data->files.infile = NULL;
	data->files.outfile = NULL;
	data->files.which_input = Stdin;
	data->files.which_output = Stdout;
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

void	ft_exit(t_minishell *data, const char *msg, char *buff, int end_program)
{
	if (buff != NULL)
		free(buff);
	if (msg != NULL)
		ft_printf(msg);
	free_input(&data->input);
	free_cmd_table(&data->cmd);
	free_files(&data->files);
	if (end_program)
	{
		rl_clear_history();
		ht_free(&data->env);
		exit(0);
	}
	else
		shell_loop(data);
}

void	shell_loop(t_minishell *data)
{
	char	*buff;

	while (1)
	{
		buff = readline("MINISHELL>");
		add_history(buff);
		if (!strncmp(buff, "exit", 5))
			ft_exit(data, NULL, buff, 1);
		tokenizer(data, buff);
		free(buff);
		if (data->input != NULL)
		{
			// display_input(data->input);
			lexer(data);
			// display_cmd_table(&data->cmd);
			exec_cmds(data);
			free_input(&data->input);
			free_cmd_table(&data->cmd);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	data;

	ft_init(&data);
	populate_env_table(&data.env, envp);
	shell_loop(&data);
	return (0);
}
