/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:42:21 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 15:45:33 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_program	*create_program(t_data *data, t_node **input, t_bool subshell)
{
	t_program	*program;

	program = (t_program *)ft_calloc(1, sizeof(t_program));
	while ((*input) && !is_connector_tok((*input)->tok))
	{
		if (subshell && (*input)->tok == TOK_CLOSE_PARENTHESIS)
			break ;
		if (is_parenthesis_tok((*input)->tok))
			handle_subsh_tok(data, program, input);
		else if ((*input)->tok == TOK_WORD)
			handle_word_tok(data, program, input);
		else if (is_redirection_tok((*input)->tok))
			handle_redir_tok(data, program, input);
	}
	return (program);
}
