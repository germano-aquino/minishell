/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:22:32 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/17 01:53:32 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	builtin_pwd(t_minishell *data, t_bool is_child)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, STDOUT);
	free(pwd);
	set_exit_value(data, is_child, EXIT_SUCCESS);
	return (TRUE);
}
