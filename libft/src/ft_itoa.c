/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:31:28 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 17:28:24 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft.h"

static void	ft_calculate_number(int number_of_digits, int n, int is_negative,
		char *number)
{
	while (number_of_digits != is_negative - 1)
	{
		number[number_of_digits] = (n % 10) + '0';
		n = n / 10;
		number_of_digits--;
	}
	if (is_negative)
		number[0] = '-';
}

static int	ft_get_number_of_digits(int n)
{
	int	number_of_digits;

	number_of_digits = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		number_of_digits++;
		n = n / 10;
	}
	return (number_of_digits);
}

char	*ft_itoa(int n)
{
	int		number_of_digits;
	int		is_negative;
	char	*number;

	number_of_digits = ft_get_number_of_digits(n);
	is_negative = 0;
	if (n < 0)
	{
		is_negative = 1;
		if (n == INT_MIN)
			return (ft_strdup("-2147483648"));
		n = -n;
	}
	number = (char *)malloc(sizeof(char) * (number_of_digits + 1 \
		+ is_negative));
	if (number == NULL)
		return (0);
	number[number_of_digits + is_negative] = '\0';
	if (!is_negative)
		number_of_digits--;
	ft_calculate_number(number_of_digits, n, is_negative, number);
	return (number);
}
