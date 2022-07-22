/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:34:02 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/22 18:36:58 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *str)
{
	char	*new_str;
	int		length;

	length = 0;
	while (str[length] != '\0')
		length++;
	new_str = malloc((length + 1) * sizeof(char));
	if (!new_str)
		return (0);
	length = 0;
	while (str[length] != '\0')
	{
		new_str[length] = str[length];
		length++;
	}
	new_str[length] = '\0';
	return (new_str);
}
