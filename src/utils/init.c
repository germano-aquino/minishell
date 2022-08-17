/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:17:18 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/16 22:09:28 by grenato-         ###   ########.fr       */
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

void	ft_open_fd_err(t_minishell *data)
{
	int	fd_err;

	close(data->fd_err);
	if (!access("tmp/err.txt", F_OK))
		unlink("tmp/err.txt");
	fd_err = open("tmp/err.txt", O_CREAT | O_WRONLY | O_APPEND, 0666);
	data->fd_err = dup(STDERR);
	dup2(fd_err, STDERR);
	close(fd_err);
}