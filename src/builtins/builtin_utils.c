/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:07:33 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/10 23:29:12 by grenato-         ###   ########.fr       */
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

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	return (ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0);
}
