/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:20:53 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 02:48:59 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	out_llong_range(char *str)
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

static void	too_many_arguments(t_data *data, char **argv, t_bool is_child)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	ft_free_matrix((void *)&argv);
	set_exit_value(data, is_child, EXIT_FAILURE);
}

static void	numeric_argument_required(t_data *data, char **argv)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(argv[1], STDERR);
	ft_putendl_fd(": numeric argument required", STDERR);
	print_error_file(data);
	close(data->fd_err);
	exit_free(data, EXIT_BAD_USAGE);
}

t_bool	builtin_exit(t_data *data, char **argv, t_bool is_child)
{
	t_llong	exit_code;

	exit_code = g_exit_value;
	if (!data->programs || !data->programs->right)
		ft_putendl_fd("exit", STDOUT);
	if (argv && argv[1])
	{
		if (out_llong_range(argv[1]) \
		|| !is_number_str(argv[1]))
			numeric_argument_required(data, argv);
		else if (argv[2])
			return (too_many_arguments(data, argv, is_child), TRUE);
		else
			exit_code = ft_atoll(argv[1]);
	}
	ft_free_matrix((void *)&argv);
	exit_free(data, exit_code);
	return (TRUE);
}
