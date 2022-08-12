/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:08:30 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 20:18:07 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_token(t_minishell *data, char *buff, size_t *i)
{
	if (!ft_strncmp((buff + *i), ">>", 2))
		*i += buff_to_input(data, ">>", Double_Great);
	else if (!ft_strncmp((buff + *i), "<<", 2))
		*i += buff_to_input(data, "<<", Double_Less);
	else if (!ft_strncmp((buff + *i), "&&", 2))
		*i += buff_to_input(data, "&&", Word);
	else if (!ft_strncmp((buff + *i), "||", 2))
		*i += buff_to_input(data, "||", Word);
	else if (!ft_strncmp((buff + *i), ">", 1))
		*i += buff_to_input(data, ">", Great);
	else if (!ft_strncmp((buff + *i), "<", 1))
		*i += buff_to_input(data, "<", Less);
	else if (!ft_strncmp((buff + *i), "|", 1))
		*i += buff_to_input(data, "|", Pipe);
	else if (!ft_strncmp((buff + *i), "&", 1))
		*i += buff_to_input(data, "&", Word);
	else if (!ft_strncmp((buff + *i), "*", 1))
		*i += buff_to_input(data, "*", Wildcard);
}

static void	escape_char_and_count(char **buff, char chr, int *count)
{
	(*count)++;
	(*buff)++;
	while (**buff && **buff != chr)
		(*buff)++;
	if (**buff)
	{
		(*count)++;
		(*buff)++;
	}
}

static int	check_unclosed_quotes(char *buff)
{
	int	quotes_amount;

	quotes_amount = 0;
	while (*buff)
	{
		if (*buff == '\'' || *buff == '\"')
			escape_char_and_count(&buff, *buff, &quotes_amount);
		else
			buff++;
	}
	return (quotes_amount % 2);
}

void	handle_parser(t_minishell *data, char *buff, size_t *i)
{
	if (ft_chr_in_str("\'", buff[*i]))
		handle_single_quote(data, buff, i);
	else if (ft_chr_in_str("\"", buff[*i]))
		handle_double_quote(data, buff, i);
	else if (!ft_strncmp((buff + *i), "$", 1))
		handle_dollar(data, buff, i);
	else
		handle_word(data, buff, i);
}

void	tokenizer(t_minishell *data, char *buff)
{
	size_t	i;

	if (check_unclosed_quotes(buff))
	{
		g_exit_value = EXIT_FAILURE;
		redisplay_prompt(data, "there are unclosed quotes", buff, FALSE);
	}
	i = 0;
	while (buff[i])
	{
		while (ft_isspace(buff[i]))
			i++;
		if (ft_chr_in_str(REGULAR_TOKENS, buff[i]))
			handle_token(data, buff, &i);
		else if (buff[i])
			handle_parser(data, buff, &i);
	}
}
