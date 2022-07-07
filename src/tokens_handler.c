/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:31 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/07 00:43:16 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*concat_and_delete_last_input(char *str, t_node *input)
{
	t_node	*last;
	char	*concat;

	last = get_last_input(input);
	concat = join_str_and_free(str, ft_strdup(last->data));
	last->prev->next = NULL;
	free_input(&last);
	return (concat);
}

void	handle_word(t_minishell *data, char *buff, int *i)
{
	char	*begin;
	char	*str;

	begin = buff + *i;
	while (ft_isalnum(buff[*i]) || ft_chr_in_str(WORD_CHARS, buff[*i]))
		(*i)++;
	str = ft_substr(begin, 0, (size_t)(buff + *i - begin));
	if (buff[*i] == '$')
	{
		handle_dollar(data, buff, i);
		str = concat_and_delete_last_input(str, data->input);
	}
	buff_to_input(data, str, Word);
	free(str);
}

void	handle_dollar(t_minishell *data, char *buff, int *i)
{
	size_t	begin;
	char	*key;
	char	*env_var;

	begin = (size_t)(++(*i));
	env_var = NULL;
	if (ft_isalpha(buff[*i]) || buff[*i] == '_')
	{
		while (ft_isalnum(buff[*i]) || buff[*i] == '_')
			(*i)++;
		key = ft_substr(buff, begin, (size_t)(*i) - begin);
		env_var = ft_strdup(ht_search(&data->env, key));
		free(key);
	}
	else if (buff[*i] == '?' && (*i)++)
		env_var = ft_itoa(data->ext_val);
	if ((ft_isalnum(buff[*i]) || ft_chr_in_str(WORD_CHARS, buff[*i])) \
		&& env_var)
	{
		handle_word(data, buff, i);
		env_var = concat_and_delete_last_input(env_var, data->input);
	}
	buff_to_input(data, env_var, Word);
	free(env_var);
}

void	handle_single_quote(t_minishell *data, char *buff, int *i)
{
	size_t	begin;
	char	*str;

	begin = (size_t)((*i)++);
	while (buff[*i] != '\'')
		(*i)++;
	(*i)++;
	str = ft_substr(buff, begin, (size_t)(*i) - begin);
	buff_to_input(data, str, Quote);
	free(str);
}

void	handle_double_quote(t_minishell *data, char *buff, int *i)
{
	size_t	begin;
	char	*str;

	begin = (*i)++;
	while (buff[*i] != '\"')
	{
		if (buff[*i] == '$')
		{
			str = ft_substr(buff, begin, (size_t)(*i) - begin);
			buff_to_input(data, str, Double_Quote);
			if (buff[*i] == '$')
				handle_dollar(data, buff, i);
			begin = (size_t)(*i);
			free(str);
		}
		else
			(*i)++;
	}
	(*i)++;
	str = ft_substr(buff, begin, (size_t)(*i) - begin);
	buff_to_input(data, str, Double_Quote);
	free(str);
}
