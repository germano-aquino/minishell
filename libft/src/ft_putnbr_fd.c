/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:33:39 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 17:32:38 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	ft_handle_negatives(int *nbr, int fd)
{
	write(fd, "-", 1);
	if (*nbr == -2147483648)
	{
		write(fd, "2147483648", 10);
		*nbr = 0;
	}
	*nbr = -*nbr;
}

void	ft_putnbr_fd(int n, int fd)
{
	char		dig;
	long int	ten_power;
	int			first_digit_no_zero;

	ten_power = 10000000000;
	first_digit_no_zero = 0;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
		ft_handle_negatives(&n, fd);
	while (ten_power)
	{
		dig = (n / ten_power) + '0';
		if (first_digit_no_zero || dig != '0')
		{
			first_digit_no_zero = 1;
			write(fd, &dig, 1);
		}
		n = n % ten_power;
		ten_power = ten_power / 10;
	}
}
