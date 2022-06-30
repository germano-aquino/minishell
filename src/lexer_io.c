/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:29:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/29 22:05:33 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_redirect_input(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if (*input != NULL && (*input)->tok == Word)
	{
		if (!access((*input)->data, F_OK | R_OK))
			data->fd[0] = open((*input)->data, O_RDONLY);
		*input = (*input)->next;
	}
	else
		ft_printf("syntax error near unexpected token \'<\'\n");
}

void	handle_redirect_output(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if (*input != NULL && (*input)->tok == Word)
	{
		if (access((*input)->data, F_OK | W_OK) == -1)
			unlink((*input)->data);
		data->fd[1] = open((*input)->data, O_CREAT | O_WRONLY, 0666);
		*input = (*input)->next;
	}
	else
		ft_printf("syntax error near unexpected token \'>\'\n");
}

void	handle_redirect_output_append(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if (*input != NULL && (*input)->tok == Word)
	{
		if (!access((*input)->data, F_OK))
			data->fd[1] = open((*input)->data, O_APPEND | O_WRONLY);
		else
			data->fd[1] = open((*input)->data, O_CREAT | O_WRONLY, 0666);
		*input = (*input)->next;
	}
	else
		ft_printf("syntax error near unexpected token \'>>\'\n");
}
