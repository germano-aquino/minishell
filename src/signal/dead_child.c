/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 10:45:15 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/22 21:47:14 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_signal_description(int sig)
{
	static char	*descriptions[EXIT_OFFSET] = {
	[SIGHUP] = "Hangup",
	[SIGQUIT] = "Quit",
	[SIGILL] = "Illegal instruction",
	[SIGTRAP] = "Trace/breakpoint trap",
	[SIGABRT] = "Aborted",
	[SIGFPE] = "Floating point exception",
	[SIGKILL] = "Killed",
	[SIGSEGV] = "Segmentation fault",
	[SIGALRM] = "Alarm clock",
	[SIGTERM] = "Terminated",
	};

	return (descriptions[sig]);
}

void	handle_dead_child(t_program *program, pid_t process_id, int status)
{
	char	*description;
	int		sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		description = get_signal_description(sig);
		if (description)
			ft_putstr_fd(description, STDERR);
		if (WCOREDUMP(status))
			ft_putstr_fd(" (core dumped)", STDERR);
		if (description != NULL)
			ft_putendl_fd("", STDERR);
		set_child_wstatus(program, process_id, (sig + EXIT_OFFSET));
	}
	else
		set_child_wstatus(program, process_id, EXIT_SUCCESS);
}
