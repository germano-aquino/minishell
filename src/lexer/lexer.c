/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:26:05 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/14 22:29:56 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_to_next_command(t_minishell *data, t_node **input, int cmd_pos)
{
	while (*input
		&& (*input)->tok != Double_Less
		&& (*input)->tok != Pipe
		&& (*input)->tok != Double_Pipe)
		*input = (*input)->next;
	ft_memfree((void *)&data->cmd.cmd_path[cmd_pos]);
	data->cmd.cmd_path[cmd_pos] = ft_strdup("");
	*data->cmd.cmd_path[cmd_pos] = -1;
}

static int	handle_connector(t_minishell *data, t_node **input, int *cmd_pos)
{
	if (!(*input)->prev || (*input)->prev->tok != Word || !(*input)->next)
		syntax_error(data, *input);
	if ((*input)-> tok == Pipe)
		data->cmd.connector[*cmd_pos] = PIPE;
	else if ((*input)-> tok == Double_Pipe)
		data->cmd.connector[*cmd_pos] = OR;
	else if ((*input)-> tok == Double_Ampersand)
		data->cmd.connector[*cmd_pos] = AND;
	*input = (*input)->next;
	(*cmd_pos)++;
	return (FALSE);
}

static void	alloc_number_of_commands(t_minishell *data, int cmds_amount)
{
	data->cmd.cmd_path = (char **)ft_calloc((cmds_amount + 1), sizeof(char *));
	data->cmd.args = (char ***)ft_calloc((cmds_amount + 1), sizeof(char **));
	data->cmd.files = (t_files *)ft_calloc(cmds_amount + 1, sizeof(t_files));
	data->cmd.connector = \
		(t_connector *)ft_calloc(cmds_amount + 1, sizeof(t_connector));
}

void	lexer(t_minishell *data)
{
	t_bool	err;
	t_node	*input;
	int		cmd_pos;

	cmd_pos = 0;
	err = FALSE;
	input = data->input;
	alloc_number_of_commands(data, (get_connectors_amount(input) + 1));
	while (input)
	{
		if (is_connector_tok(input->tok))
			err = handle_connector(data, &input, &cmd_pos);
		else if (input->tok == Word)
			err = handle_command(data, &input, cmd_pos, err);
		else
			err = handle_redir(data, &input, cmd_pos, err);
		if (err)
			skip_to_next_command(data, &input, cmd_pos);
	}
}
