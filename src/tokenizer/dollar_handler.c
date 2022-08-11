/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 00:39:17 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/11 20:41:36 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_var(t_hash_table *env, char *buff, int *i)
{
	size_t	begin;
	char	*key;
	char	*env_var;

	begin = (size_t)(*i);
	while (ft_isalnum(buff[*i]) || buff[*i] == '_')
		(*i)++;
	key = ft_substr(buff, begin, (size_t)(*i) - begin);
	env_var = ht_search(env, key);
	if (env_var)
		env_var = ft_strdup(env_var);
	free(key);
	return (env_var);
}

char	*handle_number_var(char *buff, int *i)
{
	if (buff[(*i)++] == '0')
		return (ft_strdup("minishell"));
	return (NULL);
}

char	*get_dollar_value(t_minishell *data, char *buff, int *i)
{
	char	*env_var;

	(*i)++;
	env_var = NULL;
	if (ft_isalpha(buff[*i]) || buff[*i] == '_')
		env_var = get_env_var(&data->env, buff, i);
	else if (buff[*i] == '?')
	{
		(*i)++;
		env_var = ft_itoa(g_ext_val);
	}
	else if (ft_isdigit(buff[*i]))
		env_var = handle_number_var(buff, i);
	else if (ft_isspace(buff[*i]) || buff[*i] == '\0' || buff[*i] == '\"')
		env_var = ft_strdup("$");
	else
		(*i)++;
	return (env_var);
}

void	handle_dollar(t_minishell *data, char *buff, int *i)
{
	char	*env_var;

	env_var = get_dollar_value(data, buff, i);
	if (env_var == NULL)
		return ;
	if ((buff[*i] && buff[*i] != ' '
			&& !ft_chr_in_str(REGULAR_TOKENS, buff[*i])) && env_var)
	{
		handle_parser(data, buff, i);
		env_var = concat_and_delete_last_input(env_var, data->input);
	}
	buff_to_input(data, env_var, Word);
	free(env_var);
}
