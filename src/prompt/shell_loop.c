/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 02:23:21 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 02:48:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_data *data)
{
	char	*buff;

	while (TRUE)
	{
		prompt_handler(-1, &data->env);
		trigger_signal(TRUE, &prompt_handler);
		buff = readline(get_prompt_info(&data->env));
		if (!buff)
			builtin_exit(data, NULL, FALSE);
		else if (*buff)
		{
			add_history(buff);
			open_fd_err(data);
			tokenizer(data, buff);
			ft_memfree((void *)&buff);
			lexer(data);
			execute(data, data->programs);
			print_error_file(data);
			free_minishell(data);
		}
		ft_memfree((void *)&buff);
	}
}
