/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:34:24 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 16:52:18 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_value = 0;

void	ft_init(t_minishell *data)
{
	int	i;

	i = -1;
	while (++i < HASH_TABLE_SIZE)
		data->env.item[i] = NULL;
	data->input = NULL;
	data->cmd.cmd_path = NULL;
	data->cmd.args = NULL;
	data->cmd.files = NULL;
	data->cmd.cmds_amount = 0;
	data->child_exit_code = 0;
}

void	redisplay_prompt(t_minishell *data, char *msg, char *buff, t_bool quit)
{
	if (buff)
		ft_memfree((void *)&buff);
	if (msg)
		print_error_msg(NULL, msg);
	free_input(&data->input);
	free_cmd_table(&data->cmd);
	g_exit_value = EXIT_FAILURE;
	if (quit)
		exit_free(data, EXIT_FAILURE);
	shell_loop(data);
}

void	shell_loop(t_minishell *data)
{
	char	*buff;

	buff = NULL;
	while (TRUE)
	{
		trigger_signal(TRUE, &prompt_handler);
		buff = readline("MINISHELL> ");
		if (!buff)
			builtin_exit(data, 0, FALSE);
		else if (*buff)
		{
			add_history(buff);
			tokenizer(data, buff);
			ft_memfree((void *)&buff);
			lexer(data);
			if (data->cmd.cmds_amount != 1 || !check_builtin(data, 0, FALSE))
				exec_cmds(data);
			free_input(&data->input);
			free_cmd_table(&data->cmd);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	data;

	(void)argc;
	(void)argv;
	ft_init(&data);
	populate_env_table(&data.env, envp);
	shell_loop(&data);
	return (g_exit_value);
}
