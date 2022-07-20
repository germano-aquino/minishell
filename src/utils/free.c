/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:16:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/20 15:29:19 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_files(t_files *files)
{
	if (files->infile != NULL)
	{
		free(files->infile);
		files->infile = NULL;
	}
	if (files->outfile != NULL)
	{
		free(files->outfile);
		files->outfile = NULL;
	}
	files->which_input = Stdin;
	files->which_output = Stdout;
}

void	free_cmd_table(t_command_table *table)
{
	int	i;

	i = -1;
	while (++i < table->cmds_amount)
	{
		if (table->cmd_path[i] != NULL)
		{
			free(table->cmd_path[i]);
			table->cmd_path[i] = NULL;
		}
		if (table->args[i] != NULL)
			ft_free_2d_char_ptr(&table->args[i]);
	}
	if (table->args != NULL)
	{
		free(table->args);
		table->args = NULL;
	}
	if (table->cmd_path != NULL)
	{
		free(table->cmd_path);
		table->cmd_path = NULL;
	}
	table->cmds_amount = 0;
}

void	exit_free(t_minishell *data, t_llong exit_code)
{
	rl_clear_history();
	free_input(&data->input);
	free_cmd_table(&data->cmd);
	free_files(&data->files);
	ht_free(&data->env);
	exit(exit_code);
}
