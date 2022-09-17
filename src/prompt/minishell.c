/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:18:04 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/17 01:59:14 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **envp)
{
	t_minishell	data;

	initialize_minishell(&data);
	populate_env_table(&data.env, envp);
	shell_loop(&data);
	return (g_exit_value);
}
