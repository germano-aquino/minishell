/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:26:05 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/29 22:04:11 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	handle_pipe(t_node **input)
{
	if ((*input)->prev == NULL || (*input)->prev->tok != Word)
		ft_printf("syntax error near unexpected token \'|\'\n");
	*input = (*input)->next;
}

void	lexer(t_minishell *data)
{
	t_node	*input;
	int		cmd_pos;

	cmd_pos = 0;
	input = data->input;
	alloc_number_of_commands(data, get_pipes_amount(input) + 1);
	while (input != NULL)
	{
		if (input->tok == Less)
			handle_redirect_input(data, &input);
		else if (input->tok == Great)
			handle_redirect_output(data, &input);
		else if (input->tok == Double_Great)
			handle_redirect_output_append(data, &input);
		else if (input->tok == Pipe)
			handle_pipe(&input);
		else if (input->tok == Word)
			handle_command(data, &input, &cmd_pos);
	}
}
