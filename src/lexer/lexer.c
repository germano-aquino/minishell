/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:26:05 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/15 13:09:49 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pipes_amount(t_node *input)
{
	int	pipes_amount;

	pipes_amount = 0;
	while (input)
	{
		if (input->tok == Pipe)
			pipes_amount++;
		input = input->next;
	}
	return (pipes_amount);
}

int	handle_pipe(t_minishell *data, t_node **input, int *cmd_pos)
{
	if (!(*input)->prev || (*input)->prev->tok != Word || !(*input)->next)
		redisplay_prompt(data, ERR_SYNTAX PIPE_STR, NULL, FALSE);
	*input = (*input)->next;
	(*cmd_pos)++;
	return (FALSE);
}

int	handle_input_output(t_minishell *data, t_node **input, int cmd_pos, int err)
{
	if (*input && (*input)->tok == Less)
		err = handle_redirect_input(data, input, cmd_pos);
	else if (*input
		&& ((*input)->tok == Great || (*input)->tok == Double_Great))
		err = handle_redirect_output(data, input, cmd_pos);
	else if (*input && (*input)->tok == Double_Less)
		err = handle_heredoc(data, input, cmd_pos);
	return (err);
}

void	lexer(t_minishell *data)
{
	t_bool	err;
	t_node	*input;
	int		cmd_pos;

	cmd_pos = 0;
	err = FALSE;
	input = data->input;
	alloc_number_of_commands(data, (get_pipes_amount(input) + 1));
	while (input)
	{
		if (input->tok == Pipe)
			err = handle_pipe(data, &input, &cmd_pos);
		else if (input->tok == Word)
			err = handle_command(data, &input, cmd_pos, err);
		else
			err = handle_input_output(data, &input, cmd_pos, err);
		if (err)
		{
			while (input && input->tok != Pipe)
				input = input->next;
			ft_memfree((void *)&data->cmd.cmd_path[cmd_pos]);
			data->cmd.cmd_path[cmd_pos] = ft_strdup("");
			*data->cmd.cmd_path[cmd_pos] = -1;
		}
	}
}
