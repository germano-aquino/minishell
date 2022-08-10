/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:07:33 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/10 00:50:05 by grenato-         ###   ########.fr       */
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
	if (str[0] != '_' && !ft_isalpha(str[0]))
			return (FALSE);
	index = 1;
	while (str[index])
	{
		if (str[index] != '_' && !ft_isalnum(str[index]))
			return (FALSE);
		index++;
	}
	return (TRUE);
}

void	set_exit_value(t_minishell *data, t_bool is_child, int exit_code)
{
	if (is_child)
		exit_free(data, exit_code);
	data->ext_val = exit_code;
}

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

	if (is_child == FALSE)
	{
		std_io[0] = dup(STDIN);
		std_io[1] = dup(STDOUT);
		initialize_pipes_and_pid(data->cmd.cmds_amount, &vars);
		set_input_output_fd(data, &vars);
		dup2(vars.fd[0][0], STDIN);
		dup2(vars.fd[0][1], STDOUT);
	}
	status = exec_builtin(data, index, is_child);
	if (is_child == FALSE)
	{
		dup2(std_io[0], STDIN);
		dup2(std_io[1], STDOUT);
		close(std_io[0]);
		close(std_io[1]);
	}
	return (status);
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
