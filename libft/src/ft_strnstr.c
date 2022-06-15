/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:34:27 by grenato-          #+#    #+#             */
/*   Updated: 2021/08/21 11:34:27 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t size)
{
	size_t	i;
	size_t	j;

	if (!big && !little)
		return (0);
	if (*little == '\0')
		return ((char *)big);
	i = 0;
	j = 0;
	while (i < size && big[i] != '\0')
	{
		while (big[i + j] == little[j] && little[j] != '\0')
			j++;
		if (little[j] == '\0' && i + j <= size)
			return ((char *)(big + i));
		j = 0;
		i++;
	}
	return (0);
}
