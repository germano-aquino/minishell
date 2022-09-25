/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:08:30 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/25 18:39:41 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_token(t_data *data, char *buff, size_t *i)
{
	if (ft_strncmp((buff + *i), "&&", 2) == 0)
		*i += buff_to_input(data, "&&", TOK_AND);
	else if (ft_strncmp((buff + *i), "||", 2) == 0)
		*i += buff_to_input(data, "||", TOK_OR);
	else if (ft_strncmp((buff + *i), "|", 1) == 0)
		*i += buff_to_input(data, "|", TOK_PIPE);
	else if (ft_strncmp((buff + *i), ">>", 2) == 0)
		*i += buff_to_input(data, ">>", TOK_REDIR_APPEND);
	else if (ft_strncmp((buff + *i), ">", 1) == 0)
		*i += buff_to_input(data, ">", TOK_REDIR_TRUNC);
	else if (ft_strncmp((buff + *i), "<<", 2) == 0)
		*i += buff_to_input(data, "<<", TOK_REDIR_HEREDOC);
	else if (ft_strncmp((buff + *i), "<", 1) == 0)
		*i += buff_to_input(data, "<", TOK_REDIR_INFILE);
	else if (ft_strncmp((buff + *i), "*", 1) == 0)
		*i += buff_to_input(data, "*", TOK_WILDCARD);
	else if (ft_strncmp((buff + *i), "(", 1) == 0)
		*i += buff_to_input(data, "(", TOK_OPEN_PARENTHESIS);
	else if (ft_strncmp((buff + *i), ")", 1) == 0)
		*i += buff_to_input(data, ")", TOK_CLOSE_PARENTHESIS);
	else if (ft_strncmp((buff + *i), "&", 1) == 0)
		redisplay_prompt(data, "unrecognized token `&'", buff, EXIT_BAD_USAGE);
}

static t_bool	has_unclosed_parenthesis(char *buff)
{
	int		parenthesis_amount;
	char	quote;

	parenthesis_amount = 0;
	quote = 0;
	while (*buff)
	{
		if ((*buff == SQUOTE || *buff == DQUOTE) && !quote)
			quote = *buff++;
		if ((*buff == OPEN_PARENTHESIS || *buff == CLOSE_PARENTHESIS) && !quote)
			++parenthesis_amount;
		if (quote && *buff == quote)
			quote = 0;
		buff++;
	}
	return (parenthesis_amount % 2);
}

static t_bool	has_unclosed_quotes(char *buff)
{
	int		quotes_amount;
	char	quote;

	quotes_amount = 0;
	while (*buff)
	{
		if (*buff == SQUOTE || *buff == DQUOTE)
		{
			quote = *buff;
			++buff;
			++quotes_amount;
			while (*buff && *buff != quote)
				++buff;
			if (*buff)
			{
				++buff;
				++quotes_amount;
			}
		}
		else
			buff++;
	}
	return (quotes_amount % 2);
}

void	tokenizer(t_data *data, char *buff)
{
	size_t	i;

	if (has_unclosed_quotes(buff))
		redisplay_prompt(data, ERR_QUOTES, buff, EXIT_BAD_USAGE);
	if (has_unclosed_parenthesis(buff))
		redisplay_prompt(data, ERR_PARENTHESIS, buff, EXIT_BAD_USAGE);
	i = 0;
	while (buff[i])
	{
		while (ft_isspace(buff[i]))
			i++;
		if (!!ft_strchr(REGULAR_TOKENS, buff[i]))
			handle_token(data, buff, &i);
		else if (buff[i])
			handle_parser(data, buff, &i);
	}
	wildcard_expansion(data);
	if (!data->input)
		redisplay_prompt(data, NULL, buff, EXIT_SUCCESS);
}
