/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:47:52 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 15:32:15 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_handler(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_SIGINT);
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDERR);
		exit(EXIT_SIGQUIT);
	}
}

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", TRUE);
		rl_on_new_line();
		heredoc_interruptor(TRUE);
		rl_done = TRUE;
		g_exit_value = EXIT_SIGINT;
	}
}

void	cmd_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", TRUE);
		rl_on_new_line();
		g_exit_value = EXIT_SIGINT;
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit\n");
		g_exit_value = EXIT_SIGQUIT;
	}
}

void	prompt_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", TRUE);
		rl_on_new_line();
		rl_redisplay();
		g_exit_value = EXIT_SIGINT;
	}
}

void	trigger_signal(t_bool ignore_sigquit, void *handler)
{
	t_sigaction	act;
	t_sigaction	ign;

	sigemptyset(&ign.sa_mask);
	ign.sa_handler = SIG_IGN;
	ign.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	act.sa_handler = handler;
	act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &act, NULL);
	if (ignore_sigquit)
		sigaction(SIGQUIT, &ign, NULL);
	else
		sigaction(SIGQUIT, &act, NULL);
}
