/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:31 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/02 02:12:36 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_word(t_minishell *data, char *buff, int *i)
{
	char	*begin;
	char	*str;

	begin = buff + *i;
	while (ft_isalnum(buff[*i]) || ft_chr_in_str(WORD_CHARS, buff[*i]))
		(*i)++;
	str = ft_substr(begin, 0, (size_t)(buff + *i - begin));
	buff_to_input(data, str, Word);
	free(str);
}

void	handle_forbidden_chars(t_minishell *data, char *buff, int *i)
{
	ft_printf("Invalid Chars.\n");
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
		env_var = ht_search(&data->env, key);
		free(key);
	}
	if (env_var != NULL)
		buff_to_input(data, env_var, Dollar);
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
