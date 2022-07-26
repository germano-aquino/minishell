/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:31 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/26 01:25:52 by grenato-         ###   ########.fr       */
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
	if (buff[*i] && buff[*i] != ' ' && !ft_chr_in_str(REGULAR_TOKENS, buff[*i]))
	{
		handle_parser(data, buff, i);
		str = concat_and_delete_last_input(str, data->input);
	}
	buff_to_input(data, str, Word);
	free(str);
}

void	handle_single_quote(t_minishell *data, char *buff, int *i)
{
	size_t	begin;
	char	*str;

	begin = (size_t)(++(*i));
	while (buff[*i] != '\'')
		(*i)++;
	str = ft_substr(buff, begin, (size_t)(*i) - begin);
	(*i)++;
	if (buff[*i] && buff[*i] != ' ' && !ft_chr_in_str(REGULAR_TOKENS, buff[*i]))
	{
		handle_parser(data, buff, i);
		str = concat_and_delete_last_input(str, data->input);
	}
	buff_to_input(data, str, Word);
	free(str);
}

void	handle_double_quote(t_minishell *data, char *buff, int *i)
{
	size_t	begin;
	char	*str;

	str = NULL;
	begin = ++(*i);
	while (buff[*i] != '\"')
	{
		if (buff[*i] == '$')
		{
			str = join_str_and_free(str, ft_substr(buff, begin, (size_t)(*i) - begin));
			str = join_str_and_free(str, get_dollar_value(data, buff, i));
			begin = (size_t)(*i);
		}
		else
			(*i)++;
	}
	str = join_str_and_free(str, ft_substr(buff, begin, (size_t)(*i) - begin));
	(*i)++;
	if (buff[*i] && buff[*i] != ' ' && !ft_chr_in_str(REGULAR_TOKENS, buff[*i]))
	{
		handle_parser(data, buff, i);
		str = concat_and_delete_last_input(str, data->input);
	}
	buff_to_input(data, str, Word);
	free(str);
}
