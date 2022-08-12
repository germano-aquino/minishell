/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:29:02 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/12 14:48:30 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_error(t_minishell *data, t_bool is_child, char *msg, char *dir)
{
	ft_putstr_fd("minishell: cd: ", STDERR);
	if (msg)
		ft_putendl_fd(msg, STDERR);
	else
		perror(dir);
	set_exit_value(data, is_child, EXIT_FAILURE);
	return (TRUE);
}

static void	set_env_pwd_and_oldpwd(t_minishell *data, char *oldpwd)
{
	char	*pwd;
	char	*oldpwd_env;
	char	*pwd_env;

	pwd = getcwd(NULL, 0);
	oldpwd_env = ht_search(&data->env, "OLDPWD");
	pwd_env = ht_search(&data->env, "PWD");
	if (oldpwd_env)
		ht_insert(&data->env, "OLDPWD", oldpwd);
	if (pwd_env)
		ht_insert(&data->env, "PWD", pwd);
	free(pwd);
	free(oldpwd);
}

int	builtin_cd(t_minishell *data, int index, t_bool is_child)
{
	char	*dir;
	char	*oldpwd;

	dir = data->cmd.args[index][1];
	if (dir && data->cmd.args[index][2])
		return (cd_error(data, is_child, "too many arguments", dir));
	if (!dir || ft_strcmp(dir, "~") == 0)
	{
		dir = ht_search(&data->env, "HOME");
		if (!dir)
			return (cd_error(data, is_child, "HOME not set", dir));
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		free(oldpwd);
		return (cd_error(data, is_child, NULL, dir));
	}
	set_env_pwd_and_oldpwd(data, oldpwd);
	set_exit_value(data, is_child, EXIT_SUCCESS);
	return (TRUE);
}
