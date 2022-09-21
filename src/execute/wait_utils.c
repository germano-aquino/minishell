/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:13:39 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 03:33:45 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	has_conditional_error(t_program *previous_program)
{
	if (!previous_program)
		return (FALSE);
	if (previous_program->connector == AND && previous_program->wstatus != 0)
		return (TRUE);
	if (previous_program->connector == OR && previous_program->wstatus == 0)
		return (TRUE);
	return (FALSE);
}

void	skip_pipeline(t_program **previous_program, t_program **program)
{
	while ((*program) && (*program)->connector == PIPE)
	{
		(*program)->wstatus = (*previous_program)->wstatus;
		(*previous_program) = (*program);
		(*program) = (*program)->right;
	}
	(*program)->wstatus = (*previous_program)->wstatus;
	(*previous_program) = (*program);
	(*program) = (*program)->right;
}
