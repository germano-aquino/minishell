/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redisplay.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 20:17:10 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/29 20:17:47 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redisplay_prompt(t_minishell *data, char *msg, char *buff, int status)
{
	if (msg)
		print_error_msg(NULL, msg);
	ft_memfree((void *)&buff);
	print_error_file(data);
	free_minishell(data);
	g_exit_value = status;
	shell_loop(data);
}
