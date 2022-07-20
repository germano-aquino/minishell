/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 01:33:45 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/20 00:48:34 by grenato-         ###   ########.fr       */
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

int	ft_chr_in_str(const char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			break ;
		i++;
	}
	if (str[i] != '\0')
		return (1);
	return (0);
}

char	*join_str_and_free(char *str1, char *str2)
{
	char	*join;

	if (str1 != NULL && str2 != NULL)
	{
		join = ft_strjoin(str1, str2);
		free(str1);
		free(str2);
	}
	else if (str1 == NULL && str2 != NULL)
	{
		join = ft_strdup(str2);
		free(str2);
	}
	else if (str1 != NULL && str2 == NULL)
	{
		join = ft_strdup(str1);
		free(str1);
	}
	else
		join = ft_strdup("");
	return (join);
}
