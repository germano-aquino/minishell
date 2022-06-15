/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:32:45 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 17:22:22 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	ft_normal_copy(const char *src, char *dest, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
}

static void	ft_reverse_copy(const char *src, char *dest, size_t size)
{
	size_t	i;

	i = size - 1;
	while (i + 1)
	{
		dest[i] = src[i];
		i--;
	}
}

void	*ft_memmove(void *to, const void *from, size_t size)
{
	const char	*src;
	char		*dest;

	if (!from && !to)
		return (0);
	src = (char *) from;
	dest = (char *) to;
	if (src < dest)
		ft_reverse_copy(src, dest, size);
	else
		ft_normal_copy(src, dest, size);
	return (to);
}
