/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:37:55 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/16 13:38:02 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_connector_tok(t_token token)
{
	return (token == TOK_PIPE \
	|| token == TOK_OR \
	|| token == TOK_AND);
}

t_bool	is_redirection_tok(t_token token)
{
	return (token == TOK_REDIR_INFILE \
	|| token == TOK_REDIR_HEREDOC \
	|| token == TOK_REDIR_TRUNC \
	|| token == TOK_REDIR_APPEND);
}

t_bool	is_parenthesis_tok(t_token token)
{
	return (token == TOK_OPEN_PARENTHESIS \
	|| token == TOK_CLOSE_PARENTHESIS);
}
