/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:20:53 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/23 03:48:06 by maolivei         ###   ########.fr       */
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
	ft_dprintf(STDERR, "minishell: exit: too many arguments\n");
	ft_free_matrix((void *)&argv);
	set_exit_value(data, is_child, EXIT_FAILURE);
}

static void	numeric_argument_required(t_data *data, char **argv)
{
	ft_dprintf(STDERR, "minishell: exit: %s: numeric argument required\n", \
	argv[1]);
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
