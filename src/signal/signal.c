/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:47:52 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/10 23:45:05 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (0);
}

void	child_handler(int signo)
{
	if (signo == SIGINT)
		exit(130);
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 2);
		exit(131);
	}
}

void	heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		heredoc_interruptor(1);
		rl_done = 1;
	}
	else if (signo == SIGQUIT)
		return ;
}

void	cmd_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
	}
	else if (signo == SIGQUIT)
	{
		printf("Quit\n");
	}
}

void	prompt_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		return ;
	}
}

void	trigger_signal(int ignore_sigquit, void *handler)
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
