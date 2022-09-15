/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:33:45 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/14 17:05:18 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_number_str(const char *str)
{
	size_t	index;

	index = 0;
	if (str[index] == '-' || str[index] == '+')
		++index;
	while (str[index])
		if (!ft_isdigit(str[index++]))
			return (FALSE);
	return (TRUE);
}

t_bool	is_word_str(const char *str)
{
	size_t	index;

	if (!ft_strlen(str))
		return (FALSE);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (FALSE);
	index = 1;
	while (str[index])
	{
		if (str[index] != '_' && !ft_isalnum(str[index]))
			return (FALSE);
		index++;
	}
	return (TRUE);
}

t_bool	is_connector_tok(t_token token)
{
	return (token == Pipe
		|| token == Double_Pipe
		|| token == Double_Ampersand);
}

t_bool	is_redirection_tok(t_token token)
{
	return (token == Less
		|| token == Double_Less
		|| token == Great
		|| token == Double_Great);
}

int	get_connectors_amount(t_node *input)
{
	int	connectors_amount;

	connectors_amount = 0;
	while (input)
	{
		if (is_connector_tok(input->tok))
			++connectors_amount;
		input = input->next;
	}
	return (connectors_amount);
}
