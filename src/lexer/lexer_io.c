/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:29:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/04 22:25:30 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_file(char *file, int is_append)
{
	int	fd;

	if (is_append)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	close(fd);
}

int	handle_redirect_input(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if (*input != NULL && (*input)->tok == Word)
	{
		if (!access((*input)->data, F_OK | R_OK))
		{
			if (data->files.infile != NULL)
				ft_memfree((void *) &data->files.infile);
			data->files.infile = ft_strdup((*input)->data);
			data->files.which_input = Infile;
			*input = (*input)->next;
			return (0);
		}
		else
		{
			perror((*input)->data);
			*input = (*input)->next;
			return (1);
		}
	}
	else
	{
		ft_printf("syntax error near unexpected token \'<\'\n");
		return (1);
	}
}

int	handle_redirect_output(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if (*input != NULL && (*input)->tok == Word)
	{
		if (data->files.outfile != NULL)
			ft_memfree((void *)&data->files.outfile);
		data->files.which_output = Overwrite;
		data->files.outfile = ft_strdup((*input)->data);
		create_file((*input)->data, FALSE);
		*input = (*input)->next;
		return (0);
	}
	else
	{
		ft_printf("syntax error near unexpected token \'>\'\n");
		return (1);
	}
}

int	handle_redirect_output_append(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if (*input != NULL && (*input)->tok == Word)
	{
		if (!access((*input)->data, F_OK) && access((*input)->data, W_OK) == -1)
		{
			perror((*input)->data);
			return (1);
		}
		else
		{
			if (data->files.outfile != NULL)
				ft_memfree((void *)&data->files.outfile);
			data->files.outfile = ft_strdup((*input)->data);
			data->files.which_output = Append;
			create_file((*input)->data, TRUE);
			*input = (*input)->next;
			return (0);
		}
	}
	else
	{
		ft_printf("syntax error near unexpected token \'>>\'\n");
		return (1);
	}
}

int	handle_heredoc(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if (*input != NULL && (*input)->tok == Word)
	{
		if (data->files.infile != NULL)
			ft_memfree((void *) &data->files.infile);
		data->files.infile = ft_strdup((*input)->data);
		data->files.which_input = Heredoc;
		*input = (*input)->next;
		return (0);
	}
	else
	{
		ft_printf("syntax error near unexpected token \'<<\'\n");
		return (1);
	}
}
