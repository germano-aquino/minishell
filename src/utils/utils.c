/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:33:45 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/08 15:32:52 by maolivei         ###   ########.fr       */
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
