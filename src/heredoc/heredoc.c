/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:19:44 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/19 10:53:51 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_heredoc(
	t_minishell *data, int *should_int, char *delimiter, char *line)
{
	char	*str;

	if (*should_int)
	{
		rl_done = FALSE;
		redisplay_prompt(data, NULL, line, EXIT_SIGINT);
	}
	else if (line)
		ft_memfree((void *)&line);
	else
	{
		str = ft_strdup("minishell: warning: here-document" \
			" delimited by end-of-file (wanted `%s')\n");
		printf(str, delimiter);
		ft_memfree((void *)&str);
	}
}

static int	should_close_heredoc(char *line, int *should_int, char *delimiter)
{
	int	should_close;

	should_close = (!line || *should_int);
	if (!should_close)
		should_close = ft_strcmp(line, delimiter) == 0;
	return (should_close);
}

static char	*environment_variable_expansion(t_minishell *data, char *line)
{
	char	*new_line;
	char	*temp;
	size_t	i;
	size_t	begin;

	if (!ft_chr_in_str(line, DOLLAR))
		return (line);
	i = 0;
	begin = 0;
	new_line = NULL;
	while (line[i])
	{
		if (line[i] == DOLLAR)
		{
			temp = ft_substr(line, begin, i - begin);
			new_line = ft_strjoin_free(new_line, temp);
			temp = handle_dollar(data, line, &i);
			new_line = ft_strjoin_free(new_line, temp);
			begin = i;
		}
		if (line[i])
			i++;
	}
	free(line);
	return (new_line);
}

void	ft_here_doc(t_minishell *data, char *delimiter)
{
	char	*line;
	int		fd;
	int		*should_interrupt;

	fd = open(TMP_HEREDOC_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	should_interrupt = init_heredoc_signal();
	while (TRUE)
	{
		line = readline("> ");
		if (should_close_heredoc(line, should_interrupt, delimiter))
		{
			close(fd);
			close_heredoc(data, should_interrupt, delimiter, line);
			return ;
		}
		line = environment_variable_expansion(data, line);
		ft_putendl_fd(line, fd);
		ft_memfree((void *)&line);
	}
}
