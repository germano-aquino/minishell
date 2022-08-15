/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:33:45 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/15 17:26:20 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_is_number_str(const char *str)
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

t_bool	ft_is_word_str(const char *str)
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

t_bool	ft_chr_in_str(const char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			break ;
		i++;
	}
	if (str[i])
		return (TRUE);
	return (FALSE);
}
