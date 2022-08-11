/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:34:24 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/10 23:45:52 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	data->cmd.files = NULL;
	data->ext_val = 0;
	data->child_exit_code = 0;
}

void	ft_exit(t_minishell *data, const char *msg, char *buff, int end_program)
{
	if (buff != NULL)
		free(buff);
	if (msg != NULL)
		ft_printf(msg);
	free_input(&data->input);
	free_cmd_table(&data->cmd);
	data->ext_val = EXIT_FAILURE;
	if (end_program)
	{
		rl_clear_history();
		ht_free(&data->env);
		exit(EXIT_FAILURE);
	}
	else
		shell_loop(data);
}

void	shell_loop(t_minishell *data)
{
	char	*buff;

	buff = NULL;
	while (1)
	{
		trigger_signal(1, &prompt_handler);
		buff = readline("MINISHELL> ");
		if (buff == NULL)
			builtin_exit(data, 0, FALSE);
		else if (*buff != '\0')
		{
			add_history(buff);
			tokenizer(data, buff);
			ft_memfree((void *) &buff);
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
	return (0);
}
