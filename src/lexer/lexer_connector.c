/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_connector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:46:10 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/22 05:54:41 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	has_syntax_error(t_node **input)
{
	if (!(*input)->prev)
		return (TRUE);
	else if (!(*input)->next)
	{
		if ((*input)->prev)
			(*input) = (*input)->next;
		return (TRUE);
	}
	else if ((*input)->next->tok == TOK_CLOSE_PARENTHESIS)
	{
		if ((*input)->prev)
			(*input) = (*input)->next;
		return (TRUE);
	}
	else if (is_connector_tok(((*input)->next->tok)))
	{
		if ((*input)->prev)
			(*input) = (*input)->next;
		return (TRUE);
	}
	return (FALSE);
}

void	handle_connector(t_data *data, t_program *program, t_node **input)
{
	if (has_syntax_error(input))
		syntax_error(data, (*input));
	if ((*input)-> tok == TOK_PIPE)
		program->connector = PIPE;
	else if ((*input)-> tok == TOK_OR)
		program->connector = OR;
	else if ((*input)-> tok == TOK_AND)
		program->connector = AND;
	(*input) = (*input)->next;
}
