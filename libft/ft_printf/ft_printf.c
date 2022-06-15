/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:10:35 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 15:41:29 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_print_arg(char conv_spec, int flags, va_list *ap)
{
	int	len;

	len = 0;
	if (conv_spec == 'c')
		len += ft_print_char(ap);
	else if (conv_spec == 's')
		len += ft_print_string(ap);
	else if (conv_spec == 'd' || conv_spec == 'i')
		len += ft_print_int(ap, flags);
	else if (conv_spec == 'p')
		len += ft_print_add(ap);
	else if (conv_spec == 'u')
		len += ft_print_positive_int(ap);
	else if (conv_spec == 'x')
		len += ft_print_low_hex(ap, flags);
	else if (conv_spec == 'X')
		len += ft_print_up_hex(ap, flags);
	else if (conv_spec == '%')
	{
		len++;
		write(1, "%", 1);
	}
	return (len);
}

int	ft_is_chr_in_str(const char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			break ;
		i++;
	}
	if (str[i] != '\0' || ch == '\0')
		return (1);
	return (0);
}

int	ft_get_flags(const char **format)
{
	int		flags;

	flags = 0;
	while (!ft_is_chr_in_str("csdipuxX%", **format))
	{
		if (**format == '#')
			flags |= 1;
		else if (**format == ' ')
			flags |= 2;
		else if (**format == '+')
			flags |= 4;
		(*format)++;
	}
	return (flags);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;
	int		flags;
	char	conversion_spec;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
		{
			write(1, format, 1);
			len++;
		}
		else
		{
			format++;
			flags = ft_get_flags(&format);
			conversion_spec = *format;
			len += ft_print_arg(conversion_spec, flags, &ap);
		}
		format++;
	}
	va_end(ap);
	return (len);
}
