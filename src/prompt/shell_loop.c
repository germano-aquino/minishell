/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:23:21 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/01 02:23:27 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_minishell *data)
{
	char	*buff;
	char	*prompt;

	while (TRUE)
	{
		trigger_signal(TRUE, &prompt_handler);
		prompt = get_prompt_info(&data->env);
		buff = readline(prompt);
		ft_memfree((void *)&prompt);
		if (!buff)
			builtin_exit(data, 0, FALSE);
		else if (*buff)
		{
			add_history(buff);
			open_fd_err(data);
			tokenizer(data, buff);
			ft_memfree((void *)&buff);
			lexer(data);
			if (data->cmd.cmds_amount != 1 || !check_builtin(data, 0, FALSE))
				execute_forks(data);
			print_error_file(data);
			free_minishell(data);
		}
		ft_memfree((void *)&buff);
	}
}
