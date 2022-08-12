/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:58:31 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 20:27:15 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_word(t_minishell *data, char *buff, size_t *i)
{
	char	*begin;
	char	*str;

	begin = buff + *i;
	while (buff[*i] && !ft_isspace(buff[*i])
		&& !ft_chr_in_str(REGULAR_TOKENS PARSER_TOKENS, buff[*i]))
		(*i)++;
	str = ft_substr(begin, 0, (buff + *i - begin));
	if (buff[*i] && buff[*i] != ' ' && !ft_chr_in_str(REGULAR_TOKENS, buff[*i]))
	{
		handle_parser(data, buff, i);
		str = concat_and_delete_last_input(str, &data->input);
	}
	buff_to_input(data, str, Word);
	free(str);
}

void	handle_single_quote(t_minishell *data, char *buff, size_t *i)
{
	size_t	begin;
	char	*str;

	begin = ++(*i);
	while (buff[*i] != '\'')
		(*i)++;
	str = ft_substr(buff, begin, (*i - begin));
	(*i)++;
	if (buff[*i] && buff[*i] != ' ' && !ft_chr_in_str(REGULAR_TOKENS, buff[*i]))
	{
		handle_parser(data, buff, i);
		str = concat_and_delete_last_input(str, &data->input);
	}
	buff_to_input(data, str, Word);
	free(str);
}

void	handle_double_quote(t_minishell *data, char *buff, size_t *i)
{
	size_t	begin;
	char	*str;

	str = NULL;
	begin = ++(*i);
	while (buff[*i] != '\"')
	{
		if (buff[*i] == '$')
		{
			str = join_free(str, ft_substr(buff, begin, (*i - begin)));
			str = join_free(str, get_dollar_value(data, buff, i));
			begin = *i;
		}
		else
			(*i)++;
	}
	str = join_free(str, ft_substr(buff, begin, (*i - begin)));
	(*i)++;
	if (buff[*i] && buff[*i] != ' ' && !ft_chr_in_str(REGULAR_TOKENS, buff[*i]))
	{
		handle_parser(data, buff, i);
		str = concat_and_delete_last_input(str, &data->input);
	}
	buff_to_input(data, str, Word);
	free(str);
}
