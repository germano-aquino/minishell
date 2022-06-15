/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:32:33 by grenato-          #+#    #+#             */
/*   Updated: 2021/08/21 11:32:34 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *block, int c, size_t size)
{
	char	*ptr;
	size_t	i;
	char	chr;

	ptr = (char *) block;
	i = 0;
	chr = (char) c;
	while (i < size && ptr[i] != chr)
		i++;
	if (i != size)
		return ((void *)ptr + i);
	else
		return (0);
}
