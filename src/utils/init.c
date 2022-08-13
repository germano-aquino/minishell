/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:17:18 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/13 14:17:24 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_minishell *data)
{
	int	i;

	i = -1;
	while (++i < HASH_TABLE_SIZE)
		data->env.item[i] = NULL;
	data->input = NULL;
	data->cmd.cmd_path = NULL;
	data->cmd.args = NULL;
	data->cmd.files = NULL;
	data->cmd.cmds_amount = 0;
	data->child_exit_code = 0;
}
