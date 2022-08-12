/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:19:44 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/11 22:15:46 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*heredoc_interruptor(int is_interrupt)
{
	static int	should_interrupt;

	should_interrupt = 0;
	if (is_interrupt)
		should_interrupt = 1;
	return (&should_interrupt);
}

int	*init_heredoc_signal(void)
{
	int	*should_interrupt;

	rl_event_hook = event;
	should_interrupt = heredoc_interruptor(0);
	trigger_signal(1, &heredoc_handler);
	return (should_interrupt);
}

void	close_heredoc(t_minishell *data, int *should_int,
	char *delimiter, char *line)
{
	char	*str;

	if (*should_int)
	{
		rl_done = 0;
		ft_exit(data, NULL, line, 0);
	}
	else if (line != NULL)
		ft_memfree((void *) &line);
	else
	{
		str = ft_strdup("minishell: warning: here-document" \
			" delimited by end-of-file (wanted \'%s\')\n");
		printf(str, delimiter);
		ft_memfree((void *) &str);
	}
}

int	should_close_heredoc(char *line, int *should_int, char *delimiter)
{
	int	should_close;

	should_close = (line == NULL || *should_int == 1);
	if (!should_close)
		should_close = !ft_strcmp(line, delimiter);
	return (should_close);
}

void	ft_here_doc(t_minishell *data, char *delimiter)
{
	char	*line;
	int		fd;
	int		*should_interrupt;

	fd = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	should_interrupt = init_heredoc_signal();
	while (1)
	{
		line = readline("> ");
		if (should_close_heredoc(line, should_interrupt, delimiter))
		{
			close(fd);
			close_heredoc(data, should_interrupt, delimiter, line);
			return ;
		}
		ft_putendl_fd(line, fd);
		ft_memfree((void *) &line);
	}
}
