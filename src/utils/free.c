/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:16:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/16 22:45:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_table(t_command_table *table)
{
	int	i;

	i = -1;
	while (++i < table->cmds_amount)
	{
		if (table->args[i])
			ft_free_matrix((void *)&table->args[i]);
		ft_memfree((void *)&table->cmd_path[i]);
		ft_memfree((void *)&table->files[i].infile);
		ft_memfree((void *)&table->files[i].outfile);
		table->files[i].which_input = Stdin;
		table->files[i].which_output = Stdout;
	}
	ft_memfree((void *)&table->args);
	ft_memfree((void *)&table->cmd_path);
	ft_memfree((void *)&table->files);
	table->cmds_amount = 0;
}

void	exit_free(t_minishell *data, t_llong exit_code)
{
	rl_clear_history();
	free_input(&data->input);
	free_cmd_table(&data->cmd);
	ht_free(&data->env);
	exit(exit_code);
}

void	ft_close_fd_err(t_minishell *data)
{
	dup2(data->fd_err, STDERR);
	close(data->fd_err);
	if (!access(TMP_ERROR_PATH, F_OK))
		unlink(TMP_ERROR_PATH);
}

void	free_minishell(t_minishell *data)
{
	free_input(&data->input);
	free_cmd_table(&data->cmd);
	ft_close_fd_err(data);
}
