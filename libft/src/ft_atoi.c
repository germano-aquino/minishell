/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:26:20 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 17:21:50 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_signal(const char *str, int *i)
{
	int	signal;

	signal = 1;
	if (*(str + *i) == '+' || *(str + *i) == '-')
	{
		if (*(str + *i) == '-')
			signal = -1;
		i[0]++;
	}
	return (signal);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	number;
	int	signal;
	int	count;

	i = 0;
	count = 0;
	number = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	signal = ft_get_signal(str, &i);
	while ('0' <= str[i] && str[i] <= '9')
	{
		count++;
		number = number * 10 + signal * (str[i] - '0');
		i++;
	}
	if (count > 10 && signal == -1)
		return (0);
	else if (count > 10 && signal == 1)
		return (-1);
	return (number);
}
