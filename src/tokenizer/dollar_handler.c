/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 00:39:17 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/19 10:13:46 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_env_var(t_hash_table *env, char *buff, size_t *i)
{
	size_t	begin;
	char	*key;
	char	*env_var;

	begin = (*i);
	while (ft_isalnum(buff[*i]) || buff[*i] == '_')
		(*i)++;
	key = ft_substr(buff, begin, (*i - begin));
	env_var = ht_search(env, key);
	if (env_var)
		env_var = ft_strdup(env_var);
	free(key);
	return (env_var);
}

static char	*handle_number_var(char *buff, size_t *i)
{
	if (buff[(*i)++] == '0')
		return (ft_strdup("minishell"));
	return (NULL);
}

static void	handle_heredoc_delimiter(t_minishell *data, char *buff, size_t *i)
{
	char	*delimiter;
	size_t	begin;

	begin = *i;
	while (buff[*i] && !ft_isspace(buff[*i]))
		(*i)++;
	delimiter = ft_substr(buff, begin, (*i - begin));
	buff_to_input(data, delimiter, Word);
	free(delimiter);
}

char	*get_dollar_value(t_hash_table *env, char *buff, size_t *i)
{
	char	*env_var;

	(*i)++;
	env_var = NULL;
	if (ft_isalpha(buff[*i]) || buff[*i] == '_')
		env_var = get_env_var(env, buff, i);
	else if (buff[*i] == '?')
	{
		(*i)++;
		env_var = ft_itoa(g_exit_value);
	}
	else if (ft_isdigit(buff[*i]))
		env_var = handle_number_var(buff, i);
	else if (ft_isspace(buff[*i]) || buff[*i] == '\0' || buff[*i] == DQUOTE)
		env_var = ft_strdup("$");
	else
		(*i)++;
	return (env_var);
}

char	*handle_dollar(t_minishell *data, char *buff, size_t *i)
{
	char	*env_var;
	t_node	*last_input;

	last_input = get_last_input(data->input);
	if (last_input && last_input->tok == Double_Less)
	{
		handle_heredoc_delimiter(data, buff, i);
		return (NULL);
	}
	env_var = get_dollar_value(&data->env, buff, i);
	if (!env_var)
		return (NULL);
	return (env_var);
}
