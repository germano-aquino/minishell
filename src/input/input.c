/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:22:32 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 13:37:17 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_input(const char *str, t_token tok, t_node *next, t_node *prev)
{
	t_node	*new_input;

	new_input = (t_node *)malloc(sizeof(t_node));
	new_input->data = ft_strdup(str);
	new_input->tok = tok;
	new_input->next = next;
	if (next)
		next->prev = new_input;
	new_input->prev = prev;
	if (prev)
		prev->next = new_input;
	return (new_input);
}

void	add_input(t_node **begin, t_node *new)
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

void	free_input(t_node **begin)
{
	t_node	*node;
	t_node	*tmp;

	node = *begin;
	while (node)
	{
		tmp = node;
		free(node->data);
		node = node->next;
		free(tmp);
	}
	*begin = NULL;
}

int	buff_to_input(t_minishell *data, const char *str, t_token tok)
{
	t_node	*input;
	t_node	**begin;

	begin = &data->input;
	input = create_input(str, tok, NULL, NULL);
	if (input != *begin)
		add_input(begin, input);
	return (ft_strlen(str));
}

t_node	*get_last_input(t_node *input)
{
	while (input && input->next)
		input = input->next;
	return (input);
}
