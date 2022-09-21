/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_subsh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:43:05 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 16:24:45 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_subsh_syntax(t_data *data, t_program *program, t_node *input)
{
	if (input->tok == TOK_OPEN_PARENTHESIS && input->prev \
	&& !is_connector_tok(input->prev->tok) \
	&& input->prev->tok != TOK_OPEN_PARENTHESIS)
		syntax_error(data, program, input);
	if (input->tok == TOK_OPEN_PARENTHESIS && input->next \
	&& input->next->tok != TOK_WORD \
	&& input->next->tok != TOK_OPEN_PARENTHESIS)
		syntax_error(data, program, input->next);
	if (input->tok == TOK_CLOSE_PARENTHESIS && input->next \
	&& input->next->tok == TOK_WORD \
	&& !is_parenthesis_tok(input->next->tok))
		syntax_error(data, program, input->next);
	if (input->tok == TOK_CLOSE_PARENTHESIS && (!input->prev \
	|| (input->prev->tok != TOK_WORD \
	&& !is_parenthesis_tok(input->prev->tok))))
		syntax_error(data, program, input);
}

void	handle_subsh_tok(t_data *data, t_program *program, t_node **input)
{
	t_program	*tmp;

	check_subsh_syntax(data, program, *input);
	(*input) = (*input)->next;
	program->type = SUBSHELL;
	program->left = create_program(data, input, TRUE);
	tmp = program->left;
	while ((*input) && is_connector_tok((*input)->tok) \
	&& (*input)->tok != TOK_CLOSE_PARENTHESIS)
	{
		handle_connector(data, tmp, input);
		tmp->right = create_program(data, input, TRUE);
		tmp = tmp->right;
	}
	check_subsh_syntax(data, program, *input);
	(*input) = (*input)->next;
}
