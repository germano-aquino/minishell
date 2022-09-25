/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_description.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:45:33 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/25 18:48:18 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_value_to_string(int status)
{
	char	**descriptions;
	char	*description;
	char	*str;

	str = NULL;
	if (status == 0)
	{
		ft_asprintf(&str, GREEN " \001✓\002 " RESET);
		return (str);
	}
	descriptions = ft_split(DESCRIPTIONS, ' ');
	if (status < STATUS_MIN || status > STATUS_MAX)
		description = ft_itoa(status);
	else
		description = ft_strdup(descriptions[status - STATUS_MIN]);
	ft_asprintf(&str, RED " %s \001✗\002 " RESET, description);
	ft_free_matrix((void *)&descriptions);
	ft_memfree((void *)&description);
	return (str);
}
