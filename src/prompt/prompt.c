/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:16:36 by maolivei          #+#    #+#             */
/*   Updated: 2022/08/31 14:08:41 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prompt_info(t_hash_table *env)
{
	size_t	homedir_len;
	char	*homedir;
	char	*pwd;
	char	*prompt;

	pwd = getcwd(NULL, 0);
	homedir = ht_search(env, "HOME");
	if (homedir)
		homedir_len = ft_strlen(homedir);
	if (homedir && ft_strncmp(pwd, homedir, homedir_len) == 0)
		if (pwd[homedir_len] == '/' || pwd[homedir_len] == '\0')
			pwd = ft_stredit(pwd, homedir, "~");
	prompt = ft_strjoin(NULL, "[");
	prompt = ft_strjoin_free(prompt, ft_strdup(getenv("USER")));
	prompt = ft_strjoin_free(prompt, ft_strdup("@"));
	prompt = ft_strjoin_free(prompt, ft_strdup(getenv("NAME")));
	prompt = ft_strjoin_free(prompt, ft_strdup(" "));
	prompt = ft_strjoin_free(prompt, pwd);
	prompt = ft_strjoin_free(prompt, ft_strdup("]$> "));
	return (prompt);
}

void	shell_loop(t_minishell *data)
{
	char	*buff;
	char	*prompt;

	while (TRUE)
	{
		trigger_signal(TRUE, &prompt_handler);
		prompt = get_prompt_info(&data->env);
		buff = readline(prompt);
		ft_memfree((void *)&prompt);
		if (!buff)
			builtin_exit(data, 0, FALSE);
		else if (*buff)
		{
			add_history(buff);
			open_fd_err(data);
			tokenizer(data, buff);
			ft_memfree((void *)&buff);
			lexer(data);
			if (data->cmd.cmds_amount != 1 || !check_builtin(data, 0, FALSE))
				execute_forks(data);
			print_error_file(data);
			free_minishell(data);
		}
		ft_memfree((void *)&buff);
	}
}
