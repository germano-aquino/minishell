/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_to_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:33:53 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/29 22:15:24 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node	*word_from_quote(t_node *input)
{
	char	*new_data;
	t_node	*new_input;

	new_data = ft_strtrim(input->data, "\'");
	new_input = create_input(new_data, Word, input->next, input->prev);
	free(new_data);
	input->next = NULL;
	free_input(&input);
	return (new_input);
}

t_node	*word_from_double_quote(t_node *input)
{
	t_node	*init;
	t_node	*new_input;
	char	*word;

	init = input;
	word = ft_strtrim(input->data, "\"");
	while (input->data[ft_strlen(input->data) - 1] != '\"')
	{
		input = input->next;
		if (input->data[ft_strlen(input->data) - 1] == '\"')
		{
			word = join_str_and_free(word, ft_strtrim(input->data, "\""));
			break ;
		}
		else
			word = join_str_and_free(word, ft_strdup(input->data));
	}
	new_input = create_input(word, Word, input->next, init->prev);
	free(word);
	input->next = NULL;
	free_input(&init);
	return (new_input);
}

void	transform_quotes_into_word(t_node *input)
{
	while (input != NULL)
	{
		if (input->tok == Quote)
			input = word_from_quote(input);
		else if (input->tok == Double_Quote)
			input = word_from_double_quote(input);
		input = input->next;
	}
}
