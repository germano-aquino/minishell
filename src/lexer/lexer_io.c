/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:29:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/14 00:38:08 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_file(t_node *input)
{
	int	fd;

	if (input->prev->tok == Great)
		fd = open(input->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(input->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	close(fd);
}

int	handle_redirect_input(t_minishell *data, t_node **input, int cmd_pos)
{
	if (!(*input)->next || (*input)->next->tok != Word)
		redisplay_prompt(data, ERR_SYNTAX INPUT_STR, NULL, EXIT_BAD_USAGE);
	*input = (*input)->next;
	if (access((*input)->data, R_OK) != 0)
		return (print_perror_msg(NULL, (*input)->data));
	if (data->cmd.files[cmd_pos].infile)
		ft_memfree((void *)&data->cmd.files[cmd_pos].infile);
	data->cmd.files[cmd_pos].infile = ft_strdup((*input)->data);
	data->cmd.files[cmd_pos].which_input = Infile;
	*input = (*input)->next;
	return (FALSE);
}

int	handle_redirect_output(t_minishell *data, t_node **input, int cmd_pos)
{
	if (!(*input)->next || (*input)->next->tok != Word)
	{
		if ((*input)->tok == Great)
			redisplay_prompt(data, ERR_SYNTAX TRUNC_STR, NULL, EXIT_BAD_USAGE);
		else
			redisplay_prompt(data, ERR_SYNTAX APPEND_STR, NULL, EXIT_BAD_USAGE);
	}
	*input = (*input)->next;
	if (access((*input)->data, F_OK) == 0 && access((*input)->data, W_OK) != 0)
		return (print_perror_msg(NULL, (*input)->data));
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
	if (!(*input)->next || (*input)->next->tok != Word)
		redisplay_prompt(data, ERR_SYNTAX HEREDOC_STR, NULL, EXIT_BAD_USAGE);
	*input = (*input)->next;
	if (data->cmd.files[cmd_pos].infile)
		ft_memfree((void *)&data->cmd.files[cmd_pos].infile);
	data->cmd.files[cmd_pos].infile = ft_strdup(TMP_HEREDOC_PATH);
	data->cmd.files[cmd_pos].which_input = Heredoc;
	ft_here_doc(data, (*input)->data);
	*input = (*input)->next;
	return (FALSE);
}
