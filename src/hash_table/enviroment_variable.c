/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 00:29:27 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/13 14:23:10 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	populate_env_table(t_hash_table *table, char **envp)
{
	char	*key_value[2];
	char	*aux;
	int		i;

	i = -1;
	while (envp[++i])
	{
		aux = ft_strchr(envp[i], '=');
		key_value[0] = ft_substr(envp[i], 0, (aux - envp[i]));
		key_value[1] = ft_substr(aux, 1, (ft_strlen(aux) - 1));
		ht_insert(table, key_value[0], key_value[1]);
		ft_memfree((void *)&key_value[0]);
		ft_memfree((void *)&key_value[1]);
	}
}
