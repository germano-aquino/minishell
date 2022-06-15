/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:10:40 by grenato-          #+#    #+#             */
/*   Updated: 2021/11/26 07:21:13 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# ifndef HEX_LOW
#  define HEX_LOW "0123456789abcdef"
# endif

# ifndef HEX_UP
#  define HEX_UP "0123456789ABCDEF"
# endif

# ifndef DEC
#  define DEC "0123456789"
# endif

# ifndef __APPLE__
#  define APPLE 0
# else
#  define APPLE 1
# endif

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int		ft_printf(const char *format, ...);

int		ft_print_arg(char conv_spec, int flags, va_list *ap);

int		ft_print_char(va_list *ap);

int		ft_print_string(va_list *ap);

int		ft_print_int(va_list *ap, int flags);

int		ft_print_add(va_list *ap);

int		ft_print_positive_int(va_list *ap);

int		ft_print_low_hex(va_list *ap, int flags);

int		ft_print_up_hex(va_list *ap, int flags);

char	*ft_get_base_num(size_t add, char *base);

#endif