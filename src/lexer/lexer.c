/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:26:05 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/08 23:45:45 by maolivei         ###   ########.fr       */
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
	if ((*input)->prev == NULL || (*input)->prev->tok != Word \
		|| (*input)->next == NULL || (*input)->next->tok != Word)
	{
		ft_printf("syntax error near unexpected token \'|\'\n");
		return (1);
	}
	*input = (*input)->next;
	(*cmd_pos)++;
	return (0);
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
		if (input->tok == Less)
			err = handle_redirect_input(data, &input, cmd_pos);
		else if (input->tok == Great)
			err = handle_redirect_output(data, &input, cmd_pos);
		else if (input->tok == Double_Great)
			err = handle_redirect_output_append(data, &input, cmd_pos);
		else if (input->tok == Double_Less)
			err = handle_heredoc(data, &input, cmd_pos);
		else if (input->tok == Pipe)
			err = handle_pipe(&input, &cmd_pos);
		else if (input->tok == Word)
			err = handle_command(data, &input, cmd_pos);
		if (err)
			ft_exit(data, NULL, NULL, 0);
	}
}
