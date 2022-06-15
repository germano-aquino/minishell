/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:34:15 by grenato-          #+#    #+#             */
/*   Updated: 2021/08/21 11:34:15 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	if (size)
	{
		i = 0;
		while (i + 1 < size && src[i] != '\0')
		{
			dest[i] = (unsigned char)src[i];
			i++;
		}
		dest[i] = '\0';
	}
	len = 0;
	while (src[len] != '\0')
		len++;
	return (len);
}
