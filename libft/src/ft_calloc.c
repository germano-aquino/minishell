/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:29:21 by grenato-          #+#    #+#             */
/*   Updated: 2021/08/21 11:29:23 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t eltsize)
{
	void			*ptr;
	unsigned char	*str;
	size_t			i;

	i = 0;
	ptr = malloc(count * eltsize);
	if (!ptr)
		return (0);
	str = (unsigned char *)ptr;
	while (i < count * eltsize)
	{
		str[i] = (unsigned char) 0;
		i++;
	}
	return (ptr);
}
