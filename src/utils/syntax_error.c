/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:59:00 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 16:35:57 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	word_syntax_error(t_data *data, t_node *input)
{
	char	*error;

	error = ft_strjoin(ERR_SYNTAX, "`");
	error = ft_strjoin_free(error, ft_strdup(input->data));
	error = ft_strjoin_free(error, ft_strdup("'"));
	redisplay_prompt(data, error, error, EXIT_BAD_USAGE);
}

void	syntax_error(t_data *data, t_node *input)
{
	if (!input)
		redisplay_prompt(data, ERR_SYNTAX NEWLINE_STR, NULL, EXIT_BAD_USAGE);
	else if (input->tok == TOK_REDIR_TRUNC)
		redisplay_prompt(data, ERR_SYNTAX TRUNC_STR, NULL, EXIT_BAD_USAGE);
	else if (input->tok == TOK_REDIR_APPEND)
		redisplay_prompt(data, ERR_SYNTAX APPEND_STR, NULL, EXIT_BAD_USAGE);
	else if (input->tok == TOK_REDIR_INFILE)
		redisplay_prompt(data, ERR_SYNTAX INPUT_STR, NULL, EXIT_BAD_USAGE);
	else if (input->tok == TOK_REDIR_HEREDOC)
		redisplay_prompt(data, ERR_SYNTAX HEREDOC_STR, NULL, EXIT_BAD_USAGE);
	else if (input->tok == TOK_PIPE)
		redisplay_prompt(data, ERR_SYNTAX PIPE_STR, NULL, EXIT_BAD_USAGE);
	else if (input->tok == TOK_OR)
		redisplay_prompt(data, ERR_SYNTAX OR_STR, NULL, EXIT_BAD_USAGE);
	else if (input->tok == TOK_AND)
		redisplay_prompt(data, ERR_SYNTAX AND_STR, NULL, EXIT_BAD_USAGE);
	else if (input->tok == TOK_OPEN_PARENTHESIS)
		redisplay_prompt(data, ERR_SYNTAX OPEN_STR, NULL, EXIT_BAD_USAGE);
	else if (input->tok == TOK_CLOSE_PARENTHESIS)
		redisplay_prompt(data, ERR_SYNTAX CLOSE_STR, NULL, EXIT_BAD_USAGE);
	else
		word_syntax_error(data, input);
}
