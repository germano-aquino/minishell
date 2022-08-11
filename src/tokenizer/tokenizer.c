/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:08:30 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/11 17:39:36 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_token(t_minishell *data, char *buff, int *i)
{
	if (!ft_strncmp(buff + *i, ">>", 2))
		*i += buff_to_input(data, ">>", Double_Great);
	else if (!ft_strncmp(buff + *i, "<<", 2))
		*i += buff_to_input(data, "<<", Double_Less);
	else if (!ft_strncmp(buff + *i, "&&", 2))
		*i += buff_to_input(data, "&&", Double_Ampersand);
	else if (!ft_strncmp(buff + *i, "||", 2))
		*i += buff_to_input(data, "||", Double_Pipe);
	else if (!ft_strncmp(buff + *i, ">", 1))
		*i += buff_to_input(data, ">", Great);
	else if (!ft_strncmp(buff + *i, "<", 1))
		*i += buff_to_input(data, "<", Less);
	else if (!ft_strncmp(buff + *i, "|", 1))
		*i += buff_to_input(data, "|", Pipe);
	else if (!ft_strncmp(buff + *i, "&", 1))
		*i += buff_to_input(data, "&", Ampersand);
	else if (!ft_strncmp(buff + *i, "*", 1))
		*i += buff_to_input(data, "*", Wildcard);
}

void	handle_parser(t_minishell *data, char *buff, int *i)
{
	if (ft_chr_in_str("\'", buff[*i]))
		handle_single_quote(data, buff, i);
	else if (ft_chr_in_str("\"", buff[*i]))
		handle_double_quote(data, buff, i);
	else if (!strncmp(buff + *i, "$", 1))
		handle_dollar(data, buff, i);
	else
		handle_word(data, buff, i);
}

static void	escape_char_and_count(char **buff, char chr, int *count)
{
	(*count)++;
	(*buff)++;
	while (**buff != '\0' && **buff != chr)
		(*buff)++;
	if (**buff != '\0')
	{
		(*count)++;
		(*buff)++;
	}
}

static int	check_unclosed_quotes(char *buff)
{
	int	quotes_amount;

	quotes_amount = 0;
	while (*buff != '\0')
	{
		if (*buff == '\'' || *buff == '\"')
			escape_char_and_count(&buff, *buff, &quotes_amount);
		else
			buff++;
	}
	return (quotes_amount % 2);
}

void	tokenizer(t_minishell *data, char *buff)
{
	int	i;

	i = 0;
	if (check_unclosed_quotes(buff))
		ft_exit(data, "There is unclosed quotes.\n", buff, 0);
	while (buff[i] != '\0')
	{
		while (buff[i] == ' ' || buff[i] == '\t' || buff[i] == '\n')
			i++;
		if (ft_chr_in_str(REGULAR_TOKENS, buff[i]))
			handle_token(data, buff, &i);
		else if (buff[i] != '\0')
			handle_parser(data, buff, &i);
	}
}
