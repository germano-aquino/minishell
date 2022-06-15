/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:03:11 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 15:42:13 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int	ft_print_char(va_list *ap)
{
	unsigned char	ch;

	ch = va_arg(*ap, int);
	write(1, &ch, 1);
	return (1);
}

int	ft_print_string(va_list *ap)
{
	int		len;
	char	*str;

	len = 0;
	str = va_arg(*ap, char *);
	if (str != NULL)
	{
		len = ft_strlen(str);
		ft_putstr_fd(str, 1);
	}
	else
	{
		len = 6;
		ft_putstr_fd("(null)", 1);
	}
	return (len);
}
