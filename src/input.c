/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:22:32 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/23 20:08:19 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*create_input(const char *str, t_token tok, t_node *next)
{
	t_node	*new_input;

	new_input = (t_node *)malloc(sizeof(t_node));
	new_input->data = ft_strdup(str);
	new_input->tok = tok;
	new_input->next = next;
	return (new_input);
}

void	add_input(t_node **begin, t_node *new)
{
	t_node	*last;

	if (*begin == NULL)
		*begin = new;
	else if ((*begin)->next == NULL)
		(*begin)->next = new;
	else
	{
		last = *begin;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void	display_input(t_node *input)
{
	int	i;
	char const*	tokens[] = {"Word", "File", "Dollar", "Pipe", "Double_Pipe", "Great", "Double_Great", "Less", "Double_Less", "Ampersand", "Double_Ampersand", "Quote", "Double_Quote", "Wildcard"};

	i = -1;
	if (input == NULL)
		ft_printf("Input is empty.\n");
	else
	{
		while (input != NULL)
		{
			ft_printf("i: %d\n", ++i);
			ft_printf("token: %s\ndata: %s\n\n", tokens[input->tok], input->data);
			input = input->next;
		}
	}
}

void	free_input(t_node **begin)
{
	t_node	*node;
	t_node	*tmp;

	node = *begin;
	while (node != NULL)
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
	input = create_input(str, tok, NULL);
	add_input(begin, input);
	return (ft_strlen(str));
}
