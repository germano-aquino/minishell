/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:34:24 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/20 18:30:38 by maolivei         ###   ########.fr       */
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

	buff = NULL;
	while (1)
	{
		trigger_signal(data, buff, &prompt_handler);
		buff = readline("MINISHELL> ");
		if (buff == NULL)
			ft_exit(data, "exit\n", buff, 1);
		else if (*buff != '\0')
		{
			add_history(buff);
			tokenizer(data, buff);
			ft_memfree((void *) &buff);
			lexer(data);
			if (data->cmd.cmds_amount != 1 || !check_builtin(data, 0))
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
