/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:16:36 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/12 14:17:10 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_prompt(char *user, char *hostname, char *pwd)
{
	static char	prompt[4096];
	char		*aux;

	aux = ft_strdup(MAGENTA);
	aux = ft_strjoin_free(aux, ft_strdup(user));
	aux = ft_strjoin_free(aux, ft_strdup(CYAN "@"));
	aux = ft_strjoin_free(aux, ft_strdup(MAGENTA));
	aux = ft_strjoin_free(aux, ft_strdup(hostname));
	aux = ft_strjoin_free(aux, ft_strdup(CYAN " 📁 "));
	aux = ft_strjoin_free(aux, pwd);
	if (g_exit_value == 0)
		aux = ft_strjoin_free(aux, ft_strdup(GREEN " ✓ "));
	else
	{
		aux = ft_strjoin_free(aux, ft_strdup(RED " "));
		aux = ft_strjoin_free(aux, ft_itoa(g_exit_value));
		aux = ft_strjoin_free(aux, ft_strdup(" ✗ "));
	}
	aux = ft_strjoin_free(aux, ft_strdup(RESET));
	ft_strlcpy(prompt, aux, (ft_strlen(aux) + 1));
	free(aux);
	return (prompt);
}

static char	*get_pwd_prompt(t_hash_table *env)
{
	size_t	homedir_len;
	char	*homedir;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_strdup("(unknown)"));
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
