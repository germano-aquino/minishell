/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:16:36 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/23 03:33:48 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DFL_PROMPT "%s%s%s@%s%s%s \001📁\002 %s%s \001✓\002 %s"
#define ERR_PROMPT "%s%s%s@%s%s%s \001📁\002 %s%s %d \001✗\002 %s"

static char	*build_prompt(char *user, char *hostname, char *pwd)
{
	static char	prompt[PROMPT_MAX_LENGTH];
	int			asprintf_return;
	char		*aux;

	if (g_exit_value == 0)
		asprintf_return = ft_asprintf(&aux, DFL_PROMPT, \
		PINK, user, CYAN, PINK, hostname, CYAN, pwd, GREEN, RESET);
	else
		asprintf_return = ft_asprintf(&aux, ERR_PROMPT, \
		PINK, user, CYAN, PINK, hostname, CYAN, pwd, RED, g_exit_value, RESET);
	if (asprintf_return < 0 || ft_strlen(aux) >= PROMPT_MAX_LENGTH)
		ft_strlcpy(prompt, "[unable to generate prompt]$> ", 32);
	else
		ft_strlcpy(prompt, aux, (ft_strlen(aux) + 1));
	ft_memfree((void *)&aux);
	ft_memfree((void *)&user);
	ft_memfree((void *)&hostname);
	ft_memfree((void *)&pwd);
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
		return (ft_strdup("(unknown)"));
	hostname = ft_gnl(fd, FALSE);
	close(fd);
	if (!hostname)
		return (ft_strdup("(unknown)"));
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
