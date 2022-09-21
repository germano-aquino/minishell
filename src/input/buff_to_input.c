/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_to_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 13:32:37 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 15:48:55 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_input(t_node **begin, t_node *new)
{
	t_node	*last;

	if (!*begin)
		*begin = new;
	else
	{
		last = *begin;
		while (last->next)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}

int	buff_to_input(t_data *data, char *str, t_token tok)
{
	t_node	*input;
	t_node	**begin;

	begin = &data->input;
	input = create_input(str, tok, NULL, NULL);
	add_input(begin, input);
	return (ft_strlen(str));
}
