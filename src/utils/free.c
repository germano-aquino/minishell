/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:16:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 13:24:51 by maolivei         ###   ########.fr       */
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
