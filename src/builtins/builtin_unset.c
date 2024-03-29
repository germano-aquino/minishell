/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:08:27 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 02:48:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	builtin_unset(t_data *data, char **argv, t_bool is_child)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		ht_delete(&data->env, argv[i]);
		++i;
	}
	ft_free_matrix((void *)&argv);
	set_exit_value(data, is_child, EXIT_SUCCESS);
	return (TRUE);
}
