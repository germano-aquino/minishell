/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:26:05 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/10 22:32:28 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pipes_amount(t_node *input)
{
	int	pipes_amount;

	pipes_amount = 0;
	while (input != NULL)
	{
		if (input->tok == Pipe)
			pipes_amount++;
		input = input->next;
	}
	return (pipes_amount);
}

int	handle_pipe(t_node **input, int *cmd_pos)
{
	if ((*input)->prev == NULL
		|| (*input)->prev->tok != Word
		|| (*input)->next == NULL)
	{
		ft_printf("syntax error near unexpected token \'|\'\n");
		return (1);
	}
	*input = (*input)->next;
	(*cmd_pos)++;
	return (0);
}

int	handle_input_output(t_minishell *data, t_node **input, int cmd_pos, int err)
{
	if (*input != NULL && (*input)->tok == Less)
		err = handle_redirect_input(data, input, cmd_pos);
	else if (*input != NULL
		&& ((*input)->tok == Great || (*input)->tok == Double_Great))
		err = handle_redirect_output(data, input, cmd_pos);
	else if (*input != NULL && (*input)->tok == Double_Less)
		err = handle_heredoc(data, input, cmd_pos);
	if (err)
		while (*input != NULL && (*input)->tok != Pipe)
			*input = (*input)->next;
	return (err);
}

void	lexer(t_minishell *data)
{
	t_node	*input;
	int		cmd_pos;
	int		err;

	cmd_pos = 0;
	err = 0;
	input = data->input;
	alloc_number_of_commands(data, get_pipes_amount(input) + 1);
	while (input != NULL)
	{
		if (input->tok == Pipe)
			err = handle_pipe(&input, &cmd_pos);
		else if (input->tok == Word)
			err = handle_command(data, &input, cmd_pos, err);
		else if (input != NULL)
			err = handle_input_output(data, &input, cmd_pos, err);
		if (err)
		{
			ft_memfree((void *)&data->cmd.cmd_path[cmd_pos]);
			data->cmd.cmd_path[cmd_pos] = ft_strdup("");
		}
	}
}
