/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:16:36 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/01 02:24:31 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_prompt(char *user, char *hostname, char *pwd)
{
	char	*prompt;

	prompt = ft_strdup("[");
	prompt = ft_strjoin_free(prompt, ft_strdup(user));
	prompt = ft_strjoin_free(prompt, ft_strdup("@"));
	prompt = ft_strjoin_free(prompt, ft_strdup(hostname));
	prompt = ft_strjoin_free(prompt, ft_strdup(" "));
	prompt = ft_strjoin_free(prompt, pwd);
	prompt = ft_strjoin_free(prompt, ft_strdup("]$> "));
	return (prompt);
}

static char	*get_pwd_prompt(t_hash_table *env)
{
	size_t	homedir_len;
	char	*homedir;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_strdup("unknown"));
	homedir = ht_search(env, "HOME");
	if (homedir)
		homedir_len = ft_strlen(homedir);
	if (homedir && ft_strncmp(pwd, homedir, homedir_len) == 0)
		if (pwd[homedir_len] == '/' || pwd[homedir_len] == '\0')
			pwd = ft_stredit(pwd, homedir, "~");
	return (pwd);
}

static char	*get_hostname_prompt(void)
{
	char	*hostname;

	hostname = getenv("HOSTNAME");
	if (!hostname)
		hostname = getenv("NAME");
	if (!hostname)
		hostname = "(unknown)";
	return (hostname);
}

static char	*get_user_prompt(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		user = getenv("LOGNAME");
	if (!user)
		user = "(unknown)";
	return (user);
}

char	*get_prompt_info(t_hash_table *env)
{
	char	*user;
	char	*hostname;
	char	*pwd;

	user = get_user_prompt();
	hostname = get_hostname_prompt();
	pwd = get_pwd_prompt(env);
	return (build_prompt(user, hostname, pwd));
}
