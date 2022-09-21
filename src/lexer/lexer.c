/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:26:05 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/21 16:23:36 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_data *data)
{
	t_node		*input;
	t_program	*tmp;

	input = data->input;
	data->programs = create_program(data, &input, FALSE);
	tmp = data->programs;
	while (input && is_connector_tok(input->tok))
	{
		handle_connector(data, tmp, &input);
		tmp->right = create_program(data, &input, FALSE);
		tmp = tmp->right;
	}
}
