/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:26:05 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/16 16:55:24 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_to_next_command(t_minishell *data, t_node **input, int index)
{
	while (*input \
	&& (*input)->tok != TOK_REDIR_HEREDOC \
	&& (*input)->tok != TOK_PIPE \
	&& (*input)->tok != TOK_OR)
		*input = (*input)->next;
	ft_memfree((void *)&data->cmd.cmd_path[index]);
	data->cmd.cmd_path[index] = ft_strdup("");
	*data->cmd.cmd_path[index] = -1;
}

static void	handle_parenthesis(
	t_minishell *data, t_node **input, int *curr_depth, int *high_depth)
{
	if ((*input)->tok == TOK_OPEN_PARENTHESIS \
	&& (*input)->prev && !is_connector_tok((*input)->prev->tok) \
	&& (*input)->prev->tok != TOK_OPEN_PARENTHESIS)
		syntax_error(data, *input);
	if ((*input)->tok == TOK_CLOSE_PARENTHESIS && (*input)->next \
	&& !is_connector_tok((*input)->next->tok) \
	&& !is_parenthesis_tok((*input)->next->tok))
		syntax_error(data, (*input)->next);
	if ((*input)->tok == TOK_CLOSE_PARENTHESIS \
	&& (*input)->prev->tok != TOK_WORD \
	&& !is_parenthesis_tok((*input)->prev->tok))
		syntax_error(data, *input);
	if ((*input)->tok == TOK_OPEN_PARENTHESIS)
	{
		++(*high_depth);
		*curr_depth = *high_depth;
	}
	else if ((*input)->tok == TOK_CLOSE_PARENTHESIS)
		--(*curr_depth);
	*input = (*input)->next;
}

static void	handle_connector(t_minishell *data, t_node **input, int *index)
{
	if (!(*input)->prev || !(*input)->next || ((*input)->prev->tok != TOK_WORD \
	&& !is_parenthesis_tok((*input)->prev->tok)))
		syntax_error(data, *input);
	if ((*input)-> tok == TOK_PIPE)
		data->cmd.connector[*index] = PIPE;
	else if ((*input)-> tok == TOK_OR)
		data->cmd.connector[*index] = OR;
	else if ((*input)-> tok == TOK_AND)
		data->cmd.connector[*index] = AND;
	*input = (*input)->next;
	(*index)++;
}

static void	alloc_number_of_commands(t_minishell *data, int cmds_amount)
{
	data->cmd.depth = (int *)ft_calloc(cmds_amount, sizeof(int));
	data->cmd.cmd_path = (char **)ft_calloc((cmds_amount + 1), sizeof(char *));
	data->cmd.args = (char ***)ft_calloc((cmds_amount + 1), sizeof(char **));
	data->cmd.files = (t_files *)ft_calloc((cmds_amount + 1), sizeof(t_files));
	data->cmd.connector = \
		(t_connector *)ft_calloc(cmds_amount, sizeof(t_connector));
}

void	lexer(t_minishell *data)
{
	t_bool	err;
	t_node	*input;
	int		index;
	int		current_depth;
	int		highest_depth;

	index = 0;
	input = data->input;
	current_depth = 1;
	highest_depth = 1;
	alloc_number_of_commands(data, (get_connectors_amount(input) + 1));
	while (input)
	{
		err = FALSE;
		if (is_parenthesis_tok(input->tok))
			handle_parenthesis(data, &input, &current_depth, &highest_depth);
		else if (is_connector_tok(input->tok))
			handle_connector(data, &input, &index);
		else if (input->tok == TOK_WORD)
			err = handle_command(data, &input, index, current_depth);
		else
			err = handle_redir(data, &input, index);
		if (err)
			skip_to_next_command(data, &input, index);
	}
}
