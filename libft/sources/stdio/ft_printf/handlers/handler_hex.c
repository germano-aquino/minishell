/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:30:59 by maolivei          #+#    #+#             */
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
	if (!new_str)
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

static int	fill_hex_width(t_flags *flags)
{
	size_t	i;
	char	*new_str;
	int		has_hash;

	if (flags->minus || !flags->zero)
		return (fill_width(flags));
	new_str = (char *)malloc(sizeof(char) * (flags->width + 1));
	if (!new_str)
		return (-1);
	has_hash = flags->hash * 2;
	i = 0;
	if (has_hash)
	{
		new_str[0] = '0';
		new_str[1] = flags->specifier;
	}
	while (i < (flags->width - flags->str_len))
		new_str[i++ + has_hash] = '0';
	new_str[i + has_hash] = '\0';
	ft_strlcat(new_str, (flags->str + has_hash), (flags->width + 1));
	free(flags->str);
	flags->str = new_str;
	flags->str_len = flags->width;
	return (1);
}

static int	handle_flags(t_flags *flags)
{
	char	*tmp;

	if (flags->has_precision)
		fill_precision(flags);
	if (flags->hash)
	{
		tmp = flags->str;
		flags->str = ft_strjoin("0x", tmp);
		flags->str_len += 2;
		free(tmp);
	}
	if (flags->width > flags->str_len)
		if (fill_hex_width(flags) < 0)
			return (-1);
	return (flags->str_len);
}

void	handle_hex(t_flags *flags, va_list ap)
{
	t_uint	number;

	flags->specifier = HEX_LOWER;
	if (flags->has_precision)
		flags->zero = 0;
	number = va_arg(ap, int);
	if (number == 0)
		flags->hash = 0;
	flags->str = ft_itoa_base(number, HEX_BASE);
	flags->str_len = ft_strlen(flags->str);
	if (handle_flags(flags) < 0)
		flags->has_error = TRUE;
}
