/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 13:13:52 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/12 13:31:45 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (0);
}

int	*heredoc_interruptor(int is_interrupt)
{
	static int	should_interrupt;

	should_interrupt = FALSE;
	if (is_interrupt)
		should_interrupt = TRUE;
	return (&should_interrupt);
}

int	*init_heredoc_signal(void)
{
	int	*should_interrupt;

	rl_event_hook = event;
	should_interrupt = heredoc_interruptor(FALSE);
	trigger_signal(TRUE, &heredoc_handler);
	return (should_interrupt);
}
