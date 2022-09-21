/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:29:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/21 16:36:13 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_io_file	*handle_redir_input_tok(t_node **input)
{
	t_io_file	*infile;

	infile = (t_io_file *)malloc(sizeof(t_io_file));
	infile->filename = ft_strdup((*input)->data);
	infile->io_type = IO_INFILE;
	return (infile);
}

static t_io_file	*handle_redir_output_tok(t_node **input)
{
	t_io_file	*outfile;

	outfile = (t_io_file *)malloc(sizeof(t_io_file));
	outfile->filename = ft_strdup((*input)->data);
	if ((*input)->prev->tok == TOK_REDIR_TRUNC)
		outfile->io_type = IO_TRUNC;
	else
		outfile->io_type = IO_APPEND;
	return (outfile);
}

static t_io_file	*handle_heredoc_tok(t_data *data, t_node **input)
{
	t_io_file	*heredoc;

	heredoc = (t_io_file *)malloc(sizeof(t_io_file));
	heredoc->filename = ft_strdup(TMP_HEREDOC_PATH);
	heredoc->io_type = IO_HEREDOC;
	ft_here_doc(data, (*input)->data);
	return (heredoc);
}

void	handle_redir_tok(t_data *data, t_program *program, t_node **input)
{
	t_io_file	*new_file;

	new_file = NULL;
	if (!(*input)->next || (*input)->next->tok != TOK_WORD)
	{
		free_programs(&program);
		syntax_error(data, (*input)->next);
	}
	(*input) = (*input)->next;
	if ((*input)->prev->tok == TOK_REDIR_TRUNC \
	|| (*input)->prev->tok == TOK_REDIR_APPEND)
		new_file = handle_redir_output_tok(input);
	else if ((*input)->prev->tok == TOK_REDIR_INFILE)
		new_file = handle_redir_input_tok(input);
	else if ((*input)->prev->tok == TOK_REDIR_HEREDOC)
		new_file = handle_heredoc_tok(data, input);
	if (!program->io_files)
		program->io_files = ft_lstnew(new_file);
	else
		ft_lstadd_back(&program->io_files, ft_lstnew(new_file));
	(*input) = (*input)->next;
}
