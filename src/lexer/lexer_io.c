/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:29:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/16 13:49:41 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_file(t_node *input)
{
	int	fd;

	if (input->prev->tok == TOK_REDIR_TRUNC)
		fd = open(input->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(input->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	close(fd);
}

static int	handle_redir_input(t_minishell *data, t_node **input, int index)
{
	if (access((*input)->data, R_OK) != 0)
	{
		g_exit_value = EXIT_FAILURE;
		return (print_perror_msg(NULL, (*input)->data));
	}
	if (data->cmd.files[index].infile)
		ft_memfree((void *)&data->cmd.files[index].infile);
	data->cmd.files[index].infile = ft_strdup((*input)->data);
	data->cmd.files[index].which_input = IN_INFILE;
	*input = (*input)->next;
	return (FALSE);
}

static int	handle_redir_output(t_minishell *data, t_node **input, int index)
{
	if (access((*input)->data, F_OK) == 0 && access((*input)->data, W_OK) != 0)
	{
		g_exit_value = EXIT_FAILURE;
		return (print_perror_msg(NULL, (*input)->data));
	}
	if (data->cmd.files[index].outfile)
		ft_memfree((void *)&data->cmd.files[index].outfile);
	if ((*input)->prev->tok == TOK_REDIR_TRUNC)
		data->cmd.files[index].which_output = OUT_TRUNC;
	else
		data->cmd.files[index].which_output = OUT_APPEND;
	data->cmd.files[index].outfile = ft_strdup((*input)->data);
	create_file(*input);
	*input = (*input)->next;
	return (FALSE);
}

static int	handle_heredoc(t_minishell *data, t_node **input, int index)
{
	if (data->cmd.files[index].infile)
		ft_memfree((void *)&data->cmd.files[index].infile);
	data->cmd.files[index].infile = ft_strdup(TMP_HEREDOC_PATH);
	data->cmd.files[index].which_input = IN_HEREDOC;
	ft_here_doc(data, (*input)->data);
	*input = (*input)->next;
	return (FALSE);
}

int	handle_redir(t_minishell *data, t_node **input, int index)
{
	int	err;

	err = 0;
	if (!(*input)->next || (*input)->next->tok != TOK_WORD)
		syntax_error(data, (*input)->next);
	*input = (*input)->next;
	if ((*input)->prev->tok == TOK_REDIR_TRUNC \
	|| (*input)->prev->tok == TOK_REDIR_APPEND)
		err = handle_redir_output(data, input, index);
	else if ((*input)->prev->tok == TOK_REDIR_INFILE)
		err = handle_redir_input(data, input, index);
	else if ((*input)->prev->tok == TOK_REDIR_HEREDOC)
		err = handle_heredoc(data, input, index);
	return (err);
}
