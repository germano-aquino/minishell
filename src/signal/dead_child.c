/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:45:15 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/12 14:08:31 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_signal_description(int sig)
{
	char		*description;
	static char	*descriptions[128] = {
	[SIGILL] = "Illegal instruction",
	[SIGABRT] = "Abort",
	[SIGSEGV] = "Segmentation fault",
	[SIGTERM] = "Terminated",
	[SIGHUP] = "Hangup",
	[SIGQUIT] = "Quit",
	[SIGKILL] = "Killed",
	[SIGALRM] = "Alarm clock",
	};

	description = descriptions[sig];
	return (description);
}

void	handle_dead_child(int status)
{
	char	*description;
	int		sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		description = get_signal_description(sig);
		if (description)
			printf(description);
		if (WCOREDUMP(status))
			printf(" (core dumped)");
		if (description != NULL)
			printf("\n");
		g_exit_value = sig + 128;
	}
	else
		g_exit_value = 0;
}
