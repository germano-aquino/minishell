/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:19:44 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/16 19:42:24 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	*heredoc_interruptor(int is_interrupt)
{
	static int	should_interrupt;

	should_interrupt = 0;
	if (is_interrupt)
		should_interrupt = 1;
	return (&should_interrupt);
}

int	*init_heredoc_signal(t_minishell *data)
{
	int	*should_interrupt;

	rl_event_hook = event;
	should_interrupt = heredoc_interruptor(0);
	trigger_signal(data, NULL, &heredoc_handler);
	return (should_interrupt);
}

void	close_heredoc(t_minishell *data, int *should_int, int fd[2], char *line)
{
	char	*str;

	close(fd[1]);
	if (*should_int)
	{
		rl_done = 0;
		close(fd[0]);
		ft_exit(data, NULL, line, 0);
	}
	else if (line != NULL)
		free(line);
	else
	{
		str = ft_strdup("bash: warning: here-document" \
			" delimited by end-of-file (wanted \'%s\')\n");
		ft_printf(str, data->files.infile);
		free(str);
	}
}

int	should_close_heredoc(t_minishell *data, char *line, int *should_int)
{
	int	should_close;

	should_close = (line == NULL || *should_int == 1);
	if (!should_close)
		should_close = !(ft_strncmp(line, data->files.infile, \
			max_size(line, data->files.infile)));
	return (should_close);
}

int	ft_here_doc(t_minishell *data)
{
	char	*line;
	int		fd[2];
	int		*should_interrupt;

	if (pipe(fd) == -1)
		ft_exit(data, "cannot create pipe.\n", NULL, 0);
	should_interrupt = init_heredoc_signal(data);
	while (1)
	{
		line = readline("> ");
		if (should_close_heredoc(data, line, should_interrupt))
		{
			close_heredoc(data, should_interrupt, fd, line);
			return (fd[0]);
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	return (0);
}
