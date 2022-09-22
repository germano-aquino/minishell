/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_subsh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:43:05 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 21:17:44 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	has_syntax_error(t_node **input)
{
	if ((*input)->tok == TOK_OPEN_PARENTHESIS)
	{
		if (!(*input)->next)
			return ((*input) = (*input)->next, TRUE);
		else if (is_connector_tok((*input)->next->tok))
			return ((*input) = (*input)->next, TRUE);
		else if ((*input)->next->tok == TOK_CLOSE_PARENTHESIS)
			return ((*input) = (*input)->next, TRUE);
	}
	else if ((*input)->tok == TOK_CLOSE_PARENTHESIS)
	{
		if ((*input)->next && (*input)->next->tok == TOK_WORD)
			return ((*input) = (*input)->next, TRUE);
		else if ((*input)->next && (*input)->next->tok == TOK_OPEN_PARENTHESIS)
		{
			if ((*input)->prev)
				(*input) = (*input)->next;
			return (TRUE);
		}
	}
	return (FALSE);
}

void	handle_subsh_tok(t_data *data, t_program *program, t_node **input)
{
	t_program	*tmp;

	if (has_syntax_error(input))
	{
		free_programs(&program);
		syntax_error(data, (*input));
	}
	(*input) = (*input)->next;
	program->is_subshell = TRUE;
	program->left = create_program(data, input, TRUE);
	tmp = program->left;
	while ((*input) && is_connector_tok((*input)->tok) \
	&& (*input)->tok != TOK_CLOSE_PARENTHESIS)
	{
		handle_connector(data, tmp, input);
		tmp->right = create_program(data, input, TRUE);
		tmp = tmp->right;
	}
	if (has_syntax_error(input))
	{
		free_programs(&program);
		syntax_error(data, (*input));
	}
	(*input) = (*input)->next;
}
