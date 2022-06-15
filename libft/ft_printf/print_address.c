/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:58:36 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 15:41:48 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_get_number_of_digits(size_t add, int base_len)
{
	int	number_of_digits;

	number_of_digits = 0;
	if (add == 0)
		number_of_digits = 1;
	while (add)
	{
		add /= base_len;
		number_of_digits++;
	}
	return (number_of_digits);
}

char	*ft_get_base_num(size_t add, char *base)
{
	char	*number;
	int		number_of_digits;
	int		base_len;

	base_len = ft_strlen(base);
	number_of_digits = ft_get_number_of_digits(add, base_len);
	number = (char *) malloc(sizeof(char) * (number_of_digits + 1));
	if (!number)
		return (NULL);
	number[number_of_digits] = '\0';
	while (number_of_digits)
	{
		number_of_digits--;
		number[number_of_digits] = base[add % base_len];
		add /= base_len;
	}
	return (number);
}

int	ft_print_add(va_list *ap)
{
	size_t	add;
	char	*hex_add;
	int		len;

	add = va_arg(*ap, size_t);
	if (add)
	{
		hex_add = ft_get_base_num(add, HEX_LOW);
		ft_putstr_fd("0x", 1);
		ft_putstr_fd(hex_add, 1);
		len = ft_strlen(hex_add) + 2;
		free(hex_add);
	}
	else if (APPLE)
	{
		write(1, "0x0", 3);
		len = 3;
	}
	else
	{
		write(1, "(nil)", 5);
		len = 5;
	}
	return (len);
}
