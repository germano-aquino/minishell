/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:29:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/03 19:32:14 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_redirect_input(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if (*input != NULL && (*input)->tok == Word)
	{
		if (!access((*input)->data, F_OK | R_OK))
		{
			*input = (*input)->next;
			if (data->files.infile != NULL)
				free(data->files.infile);
			data->files.infile = ft_strdup((*input)->data);
			data->files.which_input = Infile;
			return (0);
		}
		else
		{
			perror((*input)->data);
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
		if (!access((*input)->data, F_OK | W_OK))
			unlink((*input)->data);
		if (access((*input)->data, F_OK) == -1)
		{
			if (data->files.outfile != NULL)
				free(data->files.outfile);
			data->files.which_output = Overwrite;
			data->files.outfile = ft_strdup((*input)->data);
			*input = (*input)->next;
			return (0);
		}
		else
		{
			perror((*input)->data);
			return (1);
		}
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
				free(data->files.outfile);
			data->files.outfile = ft_strdup((*input)->data);
			data->files.which_output = Append;
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
