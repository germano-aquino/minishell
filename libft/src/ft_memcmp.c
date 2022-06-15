/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:32:37 by grenato-          #+#    #+#             */
/*   Updated: 2021/08/21 16:28:56 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t size)
{
	size_t			i;
	unsigned char	*pt1;
	unsigned char	*pt2;

	if (!s2 && !s1)
		return (0);
	pt1 = (unsigned char *) s1;
	pt2 = (unsigned char *) s2;
	i = 0;
	while (i < size && pt1[i] == pt2[i])
		i++;
	if (i == size)
		return (0);
	else
		return (pt1[i] - pt2[i]);
}
