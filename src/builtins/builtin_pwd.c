/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:22:32 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 02:48:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	builtin_pwd(t_data *data, char **argv, t_bool is_child)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, STDOUT);
	free(pwd);
	ft_free_matrix((void *)&argv);
	set_exit_value(data, is_child, EXIT_SUCCESS);
	return (TRUE);
}
