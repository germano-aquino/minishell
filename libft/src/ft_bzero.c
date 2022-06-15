/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:29:03 by grenato-          #+#    #+#             */
/*   Updated: 2021/08/21 11:29:05 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	ft_bzero(void *block, size_t size)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = block;
	while (i < size)
	{
		str[i] = (unsigned char) 0;
		i++;
	}
}
