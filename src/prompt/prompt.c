/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:16:36 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/14 00:41:03 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redisplay_prompt(t_minishell *data, char *msg, char *buff, int status)
{
	if (buff)
		ft_memfree((void *)&buff);
	if (msg)
		print_error_msg(NULL, msg);
	free_input(&data->input);
	free_cmd_table(&data->cmd);
	g_exit_value = status;
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
				execute_forks(data);
			free_input(&data->input);
			free_cmd_table(&data->cmd);
		}
		else
			ft_memfree((void *)&buff);
	}
}
