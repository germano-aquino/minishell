/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:16:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/31 14:08:50 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_table(t_command_table *table, t_node *input)
{
	const int	allocated_entries = get_pipes_amount(input) + 1;
	int			index;

	index = -1;
	while (++index < allocated_entries)
	{
		if (table->args && table->args[index])
			ft_free_matrix((void *)&table->args[index]);
		if (table->cmd_path && table->cmd_path[index])
			ft_memfree((void *)&table->cmd_path[index]);
		if (table->files)
		{
			ft_memfree((void *)&table->files[index].infile);
			ft_memfree((void *)&table->files[index].outfile);
			table->files[index].which_input = Stdin;
			table->files[index].which_output = Stdout;
		}
	}
	ft_memfree((void *)&table->args);
	ft_memfree((void *)&table->cmd_path);
	ft_memfree((void *)&table->files);
	table->cmds_amount = 0;
}

void	exit_free(t_minishell *data, t_llong exit_code)
{
	rl_clear_history();
	free_cmd_table(&data->cmd, data->input);
	free_input(&data->input);
	ht_free(&data->env);
	exit(exit_code);
}

void	close_fd_err(t_minishell *data)
{
	dup2(data->fd_err, STDERR);
	close(data->fd_err);
	if (!access(TMP_ERROR_PATH, F_OK))
		unlink(TMP_ERROR_PATH);
}

void	free_minishell(t_minishell *data)
{
	free_cmd_table(&data->cmd, data->input);
	free_input(&data->input);
	close_fd_err(data);
}
