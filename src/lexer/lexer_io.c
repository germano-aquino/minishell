/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:29:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 14:19:18 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_file(t_node *input)
{
	int	fd;

	if (input->prev->tok == Less)
		fd = open(input->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(input->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	close(fd);
}

int	handle_redirect_input(t_minishell *data, t_node **input, int cmd_pos)
{
	*input = (*input)->next;
	if (!*input || (*input)->tok != Word)
	{
		printf("syntax error near unexpected token \'<\'\n");
		return (TRUE);
	}
	if (access((*input)->data, R_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		perror((*input)->data);
		*input = (*input)->next;
		return (TRUE);
	}
	if (data->cmd.files[cmd_pos].infile)
		ft_memfree((void *) &data->cmd.files[cmd_pos].infile);
	data->cmd.files[cmd_pos].infile = ft_strdup((*input)->data);
	data->cmd.files[cmd_pos].which_input = Infile;
	*input = (*input)->next;
	return (FALSE);
}

int	handle_redirect_output(t_minishell *data, t_node **input, int cmd_pos)
{
	*input = (*input)->next;
	if (!*input || (*input)->tok != Word)
	{
		if ((*input)->prev->tok == Less)
			printf("syntax error near unexpected token \'>\'\n");
		else
			printf("syntax error near unexpected token \'>>\'\n");
		return (TRUE);
	}
	if (access((*input)->data, F_OK) == 0 && access((*input)->data, W_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		perror((*input)->data);
		return (TRUE);
	}
	if (data->cmd.files[cmd_pos].outfile)
		ft_memfree((void *)&data->cmd.files[cmd_pos].outfile);
	if ((*input)->prev->tok == Less)
		data->cmd.files[cmd_pos].which_output = Overwrite;
	else
		data->cmd.files[cmd_pos].which_output = Append;
	data->cmd.files[cmd_pos].outfile = ft_strdup((*input)->data);
	create_file(*input);
	*input = (*input)->next;
	return (FALSE);
}

int	handle_heredoc(t_minishell *data, t_node **input, int cmd_pos)
{
	*input = (*input)->next;
	if (!*input || (*input)->tok != Word)
	{
		printf("syntax error near unexpected token \'<<\'\n");
		return (TRUE);
	}
	if (data->cmd.files[cmd_pos].infile)
		ft_memfree((void *) &data->cmd.files[cmd_pos].infile);
	data->cmd.files[cmd_pos].infile = ft_strdup(TMP_HEREDOC_PATH);
	data->cmd.files[cmd_pos].which_input = Heredoc;
	ft_here_doc(data, (*input)->data);
	*input = (*input)->next;
	return (FALSE);
}
