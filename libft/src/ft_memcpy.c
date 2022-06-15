/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:32:41 by grenato-          #+#    #+#             */
/*   Updated: 2021/08/21 11:32:42 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *restrict to, const void *restrict from, size_t size)
{
	size_t		i;
	const char	*src;
	char		*dest;

	if (!to && !from)
		return (0);
	i = 0;
	src = from;
	dest = to;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
	return (to);
}
