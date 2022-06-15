/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:03:15 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 15:42:03 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_print_int(va_list *ap, int flags)
{
	char	*number;
	int		num;
	int		len;
	int		has_plus;
	int		has_space;

	has_plus = flags & 4;
	has_space = flags & 2;
	num = va_arg(*ap, int);
	number = ft_itoa(num);
	len = ft_strlen(number);
	if ((has_plus) && num >= 0)
		len += write(1, "+", 1);
	else if (!(has_plus) && has_space && num >= 0)
		len += write(1, " ", 1);
	ft_putstr_fd(number, 1);
	free(number);
	number = NULL;
	return (len);
}

int	ft_print_positive_int(va_list *ap)
{
	char			*number;
	unsigned int	num;
	int				len;

	num = va_arg(*ap, unsigned int);
	number = ft_get_base_num(num, DEC);
	len = ft_strlen(number);
	ft_putstr_fd(number, 1);
	free(number);
	number = NULL;
	return (len);
}

int	ft_print_low_hex(va_list *ap, int flags)
{
	char			*number;
	unsigned int	num;
	int				len;
	int				has_sharp;

	has_sharp = flags & 1;
	num = va_arg(*ap, unsigned int);
	number = ft_get_base_num(num, HEX_LOW);
	len = ft_strlen(number);
	if (has_sharp && num)
		len += write(1, "0x", 2);
	ft_putstr_fd(number, 1);
	free(number);
	number = NULL;
	return (len);
}

int	ft_print_up_hex(va_list *ap, int flags)
{
	char			*number;
	unsigned int	num;
	int				len;
	int				has_sharp;

	has_sharp = flags & 1;
	num = va_arg(*ap, unsigned int);
	number = ft_get_base_num(num, HEX_UP);
	len = ft_strlen(number);
	if (has_sharp && num)
		len += write(1, "0X", 2);
	ft_putstr_fd(number, 1);
	free(number);
	number = NULL;
	return (len);
}
