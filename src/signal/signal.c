/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:47:52 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/11 23:25:21 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		return ;
}

void	trigger_signal(t_minishell *data, char*buff, void *handler)
{
	t_sigaction	act;
	int			ttyDevice;
	t_termios	termAttr;

	ttyDevice = STDOUT_FILENO;
	if (!isatty(ttyDevice))
		return ;
	else
	{
		tcgetattr(ttyDevice, &termAttr);
		termAttr.c_cc[VQUIT] = '\0';
		tcsetattr(ttyDevice, TCSANOW, &termAttr);
	}
	act.sa_handler = handler;
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &act, NULL) == -1 || 
		sigaction(SIGQUIT, &act, NULL) == -1)
	{
		perror("sigaction");
		ft_exit(data, NULL, buff, 1);
	}
}