/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:07:33 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/26 20:52:29 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_number_str(const char *str)
{
	size_t	index;

	index = 0;
	if (str[index] == '-' || str[index] == '+')
		++index;
	while (str[index])
		if (!ft_isdigit(str[index++]))
			return (FALSE);
	return (TRUE);
}

int	ft_is_word_str(const char *str)
{
	size_t	index;

	if (!ft_strlen(str))
		return (FALSE);
	index = 0;
	while (str[index])
		if (!ft_isalpha(str[index++]))
			return (FALSE);
	return (TRUE);
}

void	set_exit_value(t_minishell *data, t_bool is_child, int exit_code)
{
	if (is_child)
		exit_free(data, exit_code);
	data->ext_val = exit_code;
}

int	check_builtin(t_minishell *data, int index, t_bool is_child)
{
	if (ft_strcmp(*data->cmd.args[index], "exit") == 0)
		return (builtin_exit(data, index, is_child));
	else if (ft_strcmp(*data->cmd.args[index], "echo") == 0)
		return (builtin_echo(data, index, is_child));
	else if (ft_strcmp(*data->cmd.args[index], "export") == 0)
		return (builtin_export(data, index, is_child));
	else if (ft_strcmp(*data->cmd.args[index], "env") == 0)
		return (builtin_env(data, is_child));
	else if (ft_strcmp(*data->cmd.args[index], "unset") == 0)
		return (builtin_unset(data, index, is_child));
	else if (ft_strcmp(*data->cmd.args[index], "cd") == 0)
		return (builtin_cd(data, index, is_child));
	else if (ft_strcmp(*data->cmd.args[index], "pwd") == 0)
		return (builtin_pwd(data, is_child));
	return (FALSE);
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0);
}
