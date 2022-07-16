/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:47:52 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/16 18:55:45 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	event(void)
{
	return (0);
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

void	trigger_signal(t_minishell *data, char*buff, void *handler)
{
	t_sigaction	act;
	t_sigaction ign;

	sigemptyset(&ign.sa_mask);
	ign.sa_handler = SIG_IGN;
	ign.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	act.sa_handler = handler;
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &act, NULL) == -1 || 
		sigaction(SIGQUIT, &ign, NULL) == -1)
	{
		perror("sigaction");
		ft_exit(data, NULL, buff, 1);
	}
}