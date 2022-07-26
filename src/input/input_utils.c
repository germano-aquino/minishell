/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:44:03 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/22 21:33:13 by maolivei         ###   ########.fr       */
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
