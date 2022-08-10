/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:05:45 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/10 17:13:41 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_minishell *data, int index, t_bool is_child)
{
	t_bool	status;

	status = FALSE;
	if (!data->cmd.args[index])
		return (TRUE);
	else if (ft_strcmp(*data->cmd.args[index], "exit") == 0)
		status = builtin_exit(data, index, is_child);
	else if (ft_strcmp(*data->cmd.args[index], "echo") == 0)
		status = builtin_echo(data, index, is_child);
	else if (ft_strcmp(*data->cmd.args[index], "export") == 0)
		status = builtin_export(data, index, is_child);
	else if (ft_strcmp(*data->cmd.args[index], "env") == 0)
		status = builtin_env(data, is_child);
	else if (ft_strcmp(*data->cmd.args[index], "unset") == 0)
		status = builtin_unset(data, index, is_child);
	else if (ft_strcmp(*data->cmd.args[index], "cd") == 0)
		status = builtin_cd(data, index, is_child);
	else if (ft_strcmp(*data->cmd.args[index], "pwd") == 0)
		status = builtin_pwd(data, is_child);
	return (status);
}

int	check_builtin(t_minishell *data, int index, t_bool is_child)
{
	t_workspace	vars;
	t_bool		status;
	int			std_io[2];

	if (!is_builtin(data->cmd.cmd_path[index]))
		return (FALSE);
	if (is_child == FALSE)
		set_io_builtin(data, &vars, std_io);
	status = exec_builtin(data, index, is_child);
	if (is_child == FALSE)
		reset_io_builtin(&vars, std_io);
	return (status);
}
