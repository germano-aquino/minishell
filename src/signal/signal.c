/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:47:52 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/23 03:43:49 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_handler(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_SIGINT);
	if (sig == SIGQUIT)
		exit(EXIT_SIGQUIT);
}

void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_value = EXIT_SIGINT;
		ft_dprintf(STDERR, "\n");
		rl_replace_line("", TRUE);
		rl_on_new_line();
		heredoc_interruptor(TRUE);
		rl_done = TRUE;
	}
}

void	cmd_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_value = EXIT_SIGINT;
		ft_dprintf(STDERR, "\n");
		rl_replace_line("", TRUE);
		rl_on_new_line();
	}
}

void	prompt_handler(int sig, t_hash_table *env)
{
	static t_hash_table	*env_reference;

	if (sig == -1)
	{
		env_reference = env;
		return ;
	}
	if (sig == SIGINT)
	{
		g_exit_value = EXIT_SIGINT;
		ft_dprintf(STDERR, "\n");
		rl_replace_line("", TRUE);
		rl_on_new_line();
		rl_set_prompt(get_prompt_info(env_reference));
		rl_redisplay();
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
