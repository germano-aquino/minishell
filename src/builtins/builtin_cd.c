/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:29:02 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/23 03:49:50 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(t_data *data, t_bool is_child, char *msg, char *dir)
{
	if (msg)
		ft_dprintf(STDERR, "minishell: cd: %s\n", msg);
	else
		ft_dprintf(STDERR, "minishell: cd: %s: %s\n", dir, strerror(errno));
	set_exit_value(data, is_child, EXIT_FAILURE);
}

static void	set_env_pwd_and_oldpwd(t_data *data, char *oldpwd)
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

t_bool	builtin_cd(t_data *data, char **argv, t_bool is_child)
{
	char	*dir;
	char	*oldpwd;

	dir = argv[1];
	if (dir && argv[2])
		return (cd_error(data, is_child, "too many arguments", dir), TRUE);
	if (!dir)
	{
		dir = ht_search(&data->env, "HOME");
		if (!dir)
			return (cd_error(data, is_child, "HOME not set", dir), TRUE);
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		free(oldpwd);
		return (cd_error(data, is_child, NULL, dir), TRUE);
	}
	set_env_pwd_and_oldpwd(data, oldpwd);
	ft_free_matrix((void *)&argv);
	set_exit_value(data, is_child, EXIT_SUCCESS);
	return (TRUE);
}
