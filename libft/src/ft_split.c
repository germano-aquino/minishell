/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:33:55 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 17:34:43 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_get_number_of_strings(const char *s, char c)
{
	int	counter;
	int	new_string_was_counted;
	int	i;

	counter = 0;
	i = 0;
	new_string_was_counted = 0;
	while (s[i] != '\0')
	{
		if (!new_string_was_counted && s[i] != c)
		{
			counter++;
			new_string_was_counted = 1;
		}
		if (new_string_was_counted && s[i] == c)
			new_string_was_counted = 0;
		i++;
	}
	return (counter);
}

static void	ft_get_valid_indexes(char const *s, char c, int *indexes)
{
	int	index;

	index = indexes[0];
	while (s[index] == c)
		index++;
	indexes[0] = index;
	while (s[index] != c && s[index] != '\0')
		index++;
	indexes[1] = index - 1;
}

static void	ft_copy_string_to_ptr(char const *s, int *indexes, char *ptr)
{
	int	i;

	i = 0;
	while (i < indexes[1] - indexes[0] + 1)
	{
		ptr[i] = s[indexes[0] + i];
		i++;
	}
	ptr[i] = '\0';
	indexes[0] = indexes[1] + 1;
}

static void	ft_variables_initiation(int *indexes)
{
	indexes[0] = 0;
	indexes[1] = 0;
	indexes[2] = 0;
}

	//ind[] is a vector of indexes where
	//ind[0] is the start index of the string to be splitted
	//ind[1] is the end index of the string to be splitted
	//ind[2] is a iterable index of split
char	**ft_split(char const *s, char c)
{
	int		ind[3];
	int		n_str;
	char	**split;

	ft_variables_initiation(ind);
	if (s == NULL)
		return (0);
	n_str = ft_get_number_of_strings(s, c);
	split = (char **) malloc(sizeof(char *) * (n_str + 1));
	if (split == NULL)
		return (0);
	while (ind[2] < n_str)
	{
		ft_get_valid_indexes(s, c, ind);
		split[ind[2]] = (char *)malloc(sizeof(char) * (ind[1] - ind[0] + 2));
		if (split[ind[2]] == NULL)
		{
			free(split);
			return (0);
		}
		ft_copy_string_to_ptr(s, ind, split[ind[2]]);
		ind[2]++;
	}
	split[ind[2]] = NULL;
	return (split);
}
