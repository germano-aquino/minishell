/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:44:03 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 14:39:06 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_last_input(t_node *begin)
{
	t_node	*last;
	t_node	*last_prev;

	last = get_last_input(begin);
	last_prev = last->prev;
	last_prev->next = NULL;
	free_input(&last);
}

char	*concat_and_delete_last_input(char *str, t_node *input)
{
	t_node	*last;
	char	*concat;

	last = get_last_input(input);
	if (last)
		concat = join_free(str, ft_strdup(last->data));
	else
		concat = join_free(str, ft_strdup(""));
	if (last && last->prev)
		last->prev->next = NULL;
	free_input(&last);
	return (concat);
}
