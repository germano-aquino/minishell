/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:17:10 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/18 17:50:43 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_llong	ft_atoll(const char *nptr)
{
	int		is_neg;
	t_llong	result;

	while (ft_isspace(*nptr))
		nptr++;
	is_neg = 1;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			is_neg = -1;
	result = 0;
	while (ft_isdigit(*nptr))
		result = (result * 10) + (*nptr++ - '0');
	return (result * is_neg);
}
