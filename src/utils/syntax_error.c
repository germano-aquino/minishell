/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:59:00 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/16 14:59:13 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	word_syntax_error(t_minishell *data, t_node *input)
{
	char	*error;

	error = ft_strjoin(ERR_SYNTAX, "`");
	error = ft_strjoin_free(error, ft_strdup(input->data));
	error = ft_strjoin_free(error, ft_strdup("'"));
	redisplay_prompt(data, error, error, EXIT_BAD_USAGE);
}

void	syntax_error(t_minishell *data, t_node *input)
{
	char	*error;

	if (!input)
		error = ft_strjoin(ERR_SYNTAX, NEWLINE_STR);
	else if (input->tok == TOK_REDIR_TRUNC)
		error = ft_strjoin(ERR_SYNTAX, TRUNC_STR);
	else if (input->tok == TOK_REDIR_APPEND)
		error = ft_strjoin(ERR_SYNTAX, APPEND_STR);
	else if (input->tok == TOK_REDIR_INFILE)
		error = ft_strjoin(ERR_SYNTAX, INPUT_STR);
	else if (input->tok == TOK_REDIR_HEREDOC)
		error = ft_strjoin(ERR_SYNTAX, HEREDOC_STR);
	else if (input->tok == TOK_PIPE)
		error = ft_strjoin(ERR_SYNTAX, PIPE_STR);
	else if (input->tok == TOK_OR)
		error = ft_strjoin(ERR_SYNTAX, OR_STR);
	else if (input->tok == TOK_AND)
		error = ft_strjoin(ERR_SYNTAX, AND_STR);
	else if (input->tok == TOK_OPEN_PARENTHESIS)
		error = ft_strjoin(ERR_SYNTAX, OPEN_STR);
	else if (input->tok == TOK_CLOSE_PARENTHESIS)
		error = ft_strjoin(ERR_SYNTAX, CLOSE_STR);
	else
		word_syntax_error(data, input);
	redisplay_prompt(data, error, error, EXIT_BAD_USAGE);
}
