/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_subsh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:43:05 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 20:12:58 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	has_syntax_error(t_node **input)
{
	if ((*input)->tok == TOK_OPEN_PARENTHESIS && (*input)->prev \
	&& !is_connector_tok((*input)->prev->tok) \
	&& (*input)->prev->tok != TOK_OPEN_PARENTHESIS)
		return (TRUE);
	if ((*input)->tok == TOK_OPEN_PARENTHESIS && (*input)->next \
	&& (*input)->next->tok != TOK_WORD \
	&& (*input)->next->tok != TOK_OPEN_PARENTHESIS)
		return ((*input) = (*input)->next, TRUE);
	if ((*input)->tok == TOK_CLOSE_PARENTHESIS && (*input)->next \
	&& (*input)->next->tok == TOK_WORD \
	&& !is_parenthesis_tok((*input)->next->tok))
		return ((*input) = (*input)->next, TRUE);
	if ((*input)->tok == TOK_CLOSE_PARENTHESIS && (!(*input)->prev \
	|| ((*input)->prev->tok != TOK_WORD \
	&& !is_parenthesis_tok((*input)->prev->tok))))
		return (TRUE);
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
