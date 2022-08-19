/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:31 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/19 10:16:06 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*handle_word(char *buff, size_t *i)
{
	char	*begin;
	char	*str;

	begin = buff + *i;
	while (buff[*i] && !ft_isspace(buff[*i])
		&& !ft_chr_in_str(REGULAR_TOKENS PARSER_TOKENS, buff[*i]))
		(*i)++;
	str = ft_substr(begin, 0, (buff + *i - begin));
	return (str);
}

static char	*handle_single_quote(char *buff, size_t *i)
{
	size_t	begin;
	char	*str;

	begin = ++(*i);
	while (buff[*i] != SQUOTE)
		(*i)++;
	str = ft_substr(buff, begin, (*i - begin));
	(*i)++;
	return (str);
}

static char	*handle_double_quote(t_minishell *data, char *buff, size_t *i)
{
	size_t	begin;
	char	*str;

	str = NULL;
	begin = ++(*i);
	while (buff[*i] != DQUOTE)
	{
		if (buff[*i] == DOLLAR)
		{
			str = ft_strjoin_free(str, ft_substr(buff, begin, (*i - begin)));
			str = ft_strjoin_free(str, get_dollar_value(&data->env, buff, i));
			begin = *i;
		}
		else
			(*i)++;
	}
	str = ft_strjoin_free(str, ft_substr(buff, begin, (*i - begin)));
	(*i)++;
	return (str);
}

void	handle_parser(t_minishell *data, char *buff, size_t *i)
{
	char	*str;

	if (buff[*i] == SQUOTE)
		str = handle_single_quote(buff, i);
	else if (buff[*i] == DQUOTE)
		str = handle_double_quote(data, buff, i);
	else if (buff[*i] == DOLLAR)
		str = handle_dollar(data, buff, i);
	else
		str = handle_word(buff, i);
	if (!str)
		return ;
	if (buff[*i] && buff[*i] != ' ' && !ft_chr_in_str(REGULAR_TOKENS, buff[*i]))
	{
		handle_parser(data, buff, i);
		str = concat_and_delete_last_input(str, &data->input);
	}
	if (ft_chr_in_str(str, '*'))
		buff_to_input(data, str, Wildcard);
	else
		buff_to_input(data, str, Word);
	free(str);
}
