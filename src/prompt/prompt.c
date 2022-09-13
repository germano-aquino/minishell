/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:16:36 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/12 21:53:51 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_prompt(char *user, char *hostname, char *pwd)
{
	static char	prompt[4096];
	char		*aux;

	aux = ft_strdup(MAGENTA);
	aux = ft_strjoin_free(aux, user);
	aux = ft_strjoin_free(aux, ft_strdup(CYAN "@"));
	aux = ft_strjoin_free(aux, ft_strdup(MAGENTA));
	aux = ft_strjoin_free(aux, hostname);
	aux = ft_strjoin_free(aux, ft_strdup(CYAN " \001📁\002 "));
	aux = ft_strjoin_free(aux, pwd);
	if (g_exit_value == 0)
		aux = ft_strjoin_free(aux, ft_strdup(GREEN " \001✓\002 "));
	else
	{
		aux = ft_strjoin_free(aux, ft_strdup(RED " "));
		aux = ft_strjoin_free(aux, ft_itoa(g_exit_value));
		aux = ft_strjoin_free(aux, ft_strdup(" \001✗\002 "));
	}
	aux = ft_strjoin_free(aux, ft_strdup(RESET));
	if (!aux || ft_strlen(aux) >= 4096)
		ft_strlcpy(prompt, "[unable to generate prompt]$> ", 32);
	else
		ft_strlcpy(prompt, aux, (ft_strlen(aux) + 1));
	ft_memfree((void *)&aux);
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
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("(unknown"));
	hostname = ft_gnl(fd);
	close(fd);
	if (!hostname)
		return (ft_strdup("(unknown"));
	hostname = ft_strtrim_free(&hostname, "\n");
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
	return (ft_strdup(user));
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
