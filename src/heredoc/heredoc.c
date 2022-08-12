/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:19:44 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 13:59:22 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc(
	t_minishell *data, int *should_int, char *delimiter, char *line)
{
	char	*str;

	if (*should_int)
	{
		rl_done = 0;
		ft_exit(data, NULL, line, 0);
	}
	else if (line)
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

	should_close = (!line || *should_int);
	if (!should_close)
		should_close = !ft_strcmp(line, delimiter);
	return (should_close);
}

void	ft_here_doc(t_minishell *data, char *delimiter)
{
	char	*line;
	int		fd;
	int		*should_interrupt;

	fd = open(TMP_HEREDOC_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
