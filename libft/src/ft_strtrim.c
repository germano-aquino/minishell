/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:34:33 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 17:25:19 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_is_char_in_set(char chr, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == chr)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_get_strtrim_length(char const *str, char const *set)
{
	int	start_index;
	int	end_index;

	start_index = 0;
	while (ft_is_char_in_set(str[start_index], set))
		start_index++;
	if (str[start_index] == '\0')
		return (0);
	end_index = start_index;
	while (str[end_index] != '\0')
		end_index++;
	end_index--;
	while (ft_is_char_in_set(str[end_index], set))
		end_index--;
	return (end_index - start_index + 1);
}

char	*ft_strtrim(char const *str, char const *set)
{
	int		len;
	int		start_index;
	int		i;
	char	*ptr;

	if (str == NULL)
		return (0);
	len = ft_get_strtrim_length(str, set);
	ptr = (char *) malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (0);
	start_index = 0;
	while (ft_is_char_in_set(str[start_index], set))
		start_index++;
	i = 0;
	while (i < len)
	{
		ptr[i] = str[start_index + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
