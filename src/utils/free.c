/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 00:16:50 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/22 13:39:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_free(t_data *data, int exit_code)
{
	rl_clear_history();
	free_programs(&data->programs);
	free_input(&data->input);
	ht_free(&data->env);
	exit(exit_code);
}

void	clear_program_file(void *content)
{
	t_io_file	*io_file;

	io_file = (t_io_file *)content;
	ft_memfree((void *)&io_file->filename);
	ft_memfree(&content);
}

void	free_programs(t_program **programs)
{
	if (!(*programs))
		return ;
	free_programs(&(*programs)->right);
	free_programs(&(*programs)->left);
	ft_memfree((void *)&(*programs)->path);
	ft_lstclear(&(*programs)->arguments, free);
	ft_lstclear(&(*programs)->io_files, clear_program_file);
	ft_memfree((void *)programs);
}

void	free_minishell(t_data *data)
{
	data->should_wait = 0;
	data->previous_program = NULL;
	free_programs(&data->programs);
	free_input(&data->input);
}
