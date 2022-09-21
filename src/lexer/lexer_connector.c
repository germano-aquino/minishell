/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_connector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:46:10 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 16:35:35 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_connector(t_data *data, t_program *program, t_node **input)
{
	if (!(*input)->prev || !(*input)->next || ((*input)->prev->tok != TOK_WORD \
	&& !is_parenthesis_tok((*input)->prev->tok)))
		syntax_error(data, *input);
	if ((*input)-> tok == TOK_PIPE)
		program->connector = PIPE;
	else if ((*input)-> tok == TOK_OR)
		program->connector = OR;
	else if ((*input)-> tok == TOK_AND)
		program->connector = AND;
	(*input) = (*input)->next;
}
