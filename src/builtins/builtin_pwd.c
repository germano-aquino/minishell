/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:22:32 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/26 20:55:51 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_minishell *data, t_bool is_child)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	set_exit_value(data, is_child, EXIT_SUCCESS);
	return (TRUE);
}
