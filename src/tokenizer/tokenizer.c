/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:08:30 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/31 14:09:50 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_token(t_minishell *data, char *buff, size_t *i)
{
	if (ft_strncmp((buff + *i), ">>", 2) == 0)
		*i += buff_to_input(data, ">>", Double_Great);
	else if (ft_strncmp((buff + *i), "<<", 2) == 0)
		*i += buff_to_input(data, "<<", Double_Less);
	else if (ft_strncmp((buff + *i), "&&", 2) == 0)
		*i += buff_to_input(data, "&&", Word);
	else if (ft_strncmp((buff + *i), "||", 2) == 0)
		*i += buff_to_input(data, "||", Word);
	else if (ft_strncmp((buff + *i), ">", 1) == 0)
		*i += buff_to_input(data, ">", Great);
	else if (ft_strncmp((buff + *i), "<", 1) == 0)
		*i += buff_to_input(data, "<", Less);
	else if (ft_strncmp((buff + *i), "|", 1) == 0)
		*i += buff_to_input(data, "|", Pipe);
	else if (ft_strncmp((buff + *i), "&", 1) == 0)
		*i += buff_to_input(data, "&", Word);
	else if (ft_strncmp((buff + *i), "*", 1) == 0)
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
		if (*buff == SQUOTE || *buff == DQUOTE)
			escape_char_and_count(&buff, *buff, &quotes_amount);
		else
			buff++;
	}
	return (quotes_amount % 2);
}

void	tokenizer(t_minishell *data, char *buff)
{
	size_t	i;

	if (check_unclosed_quotes(buff))
		redisplay_prompt(data, ERR_QUOTES, buff, EXIT_BAD_USAGE);
	i = 0;
	while (buff[i])
	{
		while (ft_isspace(buff[i]))
			i++;
		if (is_chr_in_str(REGULAR_TOKENS, buff[i]))
			handle_token(data, buff, &i);
		else if (buff[i])
			handle_parser(data, buff, &i);
	}
	wildcard_expansion(data);
	if (!data->input)
		redisplay_prompt(data, NULL, buff, EXIT_SUCCESS);
}
