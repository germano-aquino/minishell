/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:29:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/22 22:53:42 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_file(t_node *input)
{
	int	fd;

	if (input->prev->tok == Great)
		fd = open(input->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(input->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	close(fd);
}

static int	handle_redir_input(t_minishell *data, t_node **input, int cmd_pos)
{
	if (access((*input)->data, R_OK) != 0)
	{
		g_exit_value = EXIT_FAILURE;
		return (print_perror_msg(NULL, (*input)->data));
	}
	if (data->cmd.files[cmd_pos].infile)
		ft_memfree((void *)&data->cmd.files[cmd_pos].infile);
	data->cmd.files[cmd_pos].infile = ft_strdup((*input)->data);
	data->cmd.files[cmd_pos].which_input = Infile;
	*input = (*input)->next;
	return (FALSE);
}

static int	handle_redir_output(t_minishell *data, t_node **input, int cmd_pos)
{
	if (access((*input)->data, F_OK) == 0 && access((*input)->data, W_OK) != 0)
		return (print_perror_msg(NULL, (*input)->data));
	if (data->cmd.files[cmd_pos].outfile)
		ft_memfree((void *)&data->cmd.files[cmd_pos].outfile);
	if ((*input)->prev->tok == Great)
		data->cmd.files[cmd_pos].which_output = Truncate;
	else
		data->cmd.files[cmd_pos].which_output = Append;
	data->cmd.files[cmd_pos].outfile = ft_strdup((*input)->data);
	create_file(*input);
	*input = (*input)->next;
	return (FALSE);
}

static int	handle_heredoc(t_minishell *data, t_node **input, int cmd_pos)
{
	if (data->cmd.files[cmd_pos].infile)
		ft_memfree((void *)&data->cmd.files[cmd_pos].infile);
	data->cmd.files[cmd_pos].infile = ft_strdup(TMP_HEREDOC_PATH);
	data->cmd.files[cmd_pos].which_input = Heredoc;
	ft_here_doc(data, (*input)->data);
	*input = (*input)->next;
	return (FALSE);
}

int	handle_redir(t_minishell *data, t_node **input, int cmd_pos, int err)
{
	if (!(*input)->next || (*input)->next->tok != Word)
		syntax_error(data, (*input)->next);
	*input = (*input)->next;
	if ((*input)->prev->tok == Great || (*input)->prev->tok == Double_Great)
		err = handle_redir_output(data, input, cmd_pos);
	else if ((*input)->prev->tok == Less)
		err = handle_redir_input(data, input, cmd_pos);
	else if ((*input)->prev->tok == Double_Less)
		err = handle_heredoc(data, input, cmd_pos);
	return (err);
}
