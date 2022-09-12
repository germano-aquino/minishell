/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:17:18 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/12 12:04:29 by maolivei         ###   ########.fr       */
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
}

void	open_fd_err(t_minishell *data)
{
	int	fd_err;

	data->fd_err = dup(STDERR);
	if (!access(TMP_ERROR_PATH, F_OK))
		unlink(TMP_ERROR_PATH);
	fd_err = open(TMP_ERROR_PATH, O_CREAT | O_WRONLY | O_APPEND, 0666);
	dup2(fd_err, STDERR);
	close(fd_err);
}
