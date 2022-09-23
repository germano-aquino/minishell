/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:18:07 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/23 00:29:47 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_zero(t_flags *flags)
{
	if (flags->str[0] == '0')
	{
		free(flags->str);
		flags->str = ft_strdup("");
		flags->str_len = 0;
	}
	return (flags->precision);
}

static int	fill_precision(t_flags *flags)
{
	int		i;
	int		str_len;
	char	*new_str;

	if (flags->precision == 0)
		return (handle_zero(flags));
	str_len = ft_strlen(flags->str);
	if (str_len >= flags->precision)
		return (str_len);
	new_str = (char *)malloc(sizeof(char) * (flags->precision + 1));
	if (new_str)
		return (-1);
	i = 0;
	new_str[flags->precision] = '\0';
	while (i < (flags->precision - str_len))
		new_str[i++] = '0';
	new_str[i] = '\0';
	ft_strlcat(new_str, flags->str, (flags->precision + 1));
	free(flags->str);
	flags->str = new_str;
	flags->str_len = flags->precision;
	return (flags->precision);
}

int	print_intu(t_flags *flags)
{
	if (flags->has_precision)
		fill_precision(flags);
	if (flags->width > flags->str_len)
		if (fill_int_width(flags) < 0)
			return (-1);
	return (flags->str_len);
}

void	handle_unsigned(t_flags *flags, va_list ap)
{
	flags->specifier = UNSIGNED;
	if (flags->has_precision)
		flags->zero = 0;
	flags->str = ft_utoa(va_arg(ap, int));
	flags->str_len = ft_strlen(flags->str);
	print_intu(flags);
}
