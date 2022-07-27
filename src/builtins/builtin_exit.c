/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:20:53 by maolivei          #+#    #+#             */
/*   Updated: 2022/07/26 20:54:52 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	out_llong_range(char *str)
{
	t_bool	sign;

	sign = FALSE;
	if (*str == '-' || *str == '+')
		sign = TRUE;
	if (ft_strlen(str) > (20 + sign))
		return (TRUE);
	else if (!sign && (ft_strcmp("9223372036854775807", str) < 0))
		return (TRUE);
	else if (*str == '+' && (ft_strcmp("+9223372036854775807", str) < 0))
		return (TRUE);
	else if (*str == '-' && (ft_strcmp("-9223372036854775808", str) < 0))
		return (TRUE);
	return (FALSE);
}

static int	too_many_arguments(t_minishell *data, t_bool is_child)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	set_exit_value(data, is_child, EXIT_FAILURE);
	return (TRUE);
}

static void	numeric_argument_required(t_minishell *data, int index)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(data->cmd.args[index][1], STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit_free(data, 2);
}

int	builtin_exit(t_minishell *data, int index, t_bool is_child)
{
	t_llong	exit_code;

	exit_code = data->ext_val;
	if (data->cmd.cmds_amount <= 1)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (data->cmd.args && data->cmd.args[index][1])
	{
		if (out_llong_range(data->cmd.args[index][1])
			|| !ft_is_number_str(data->cmd.args[index][1]))
			numeric_argument_required(data, index);
		else if (data->cmd.args[index][2])
			return (too_many_arguments(data, is_child));
		else
			exit_code = ft_atoll(data->cmd.args[index][1]);
	}
	exit_free(data, exit_code);
	return (TRUE);
}
