/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:33:45 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/23 20:17:13 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	max_size(char *s1, char *s2)
{
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(s1) + 1;
	size2 = ft_strlen(s2) + 1;
	if (size1 > size2)
		return (size1);
	else
		return (size2);
}

void	ft_free_2d_char_ptr(char ***ptr)
{
	char	**temp;
	int		i;

	temp = *ptr;
	i = 0;
	while (*temp != NULL)
	{
		free(*temp);
		*temp = NULL;
		i++;
		temp = (*ptr + i);
	}
	free(*ptr);
	*ptr = NULL;
}
