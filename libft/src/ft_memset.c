/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:33:28 by grenato-          #+#    #+#             */
/*   Updated: 2021/08/21 11:33:29 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *block, int c, size_t size)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = block;
	while (i < size)
	{
		str[i] = (unsigned char) c;
		i++;
	}
	return (block);
}
