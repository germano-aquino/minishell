/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:08:30 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/15 03:22:51 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_quotes(t_minishell *data, char *buff, int *i)
{
	char	*begin;
	char	*str;

	begin = buff + *i;
	if (buff[*i] == '\'')
	{
		(*i)++;
		while (buff[*i] != '\'')
			(*i)++;
		str = ft_substr(begin, 0, (size_t)(buff + *i - begin));
		buff_to_input(data, str, Quote);
		free(str);
	}
	if (buff[*i] == '\"')
	{
		(*i)++;
		while (buff[*i] != '\"')
			(*i)++;
		str = ft_substr(begin, 0, (size_t)(buff + *i - begin));
		buff_to_input(data, str, Double_Quote);
		free(str);
	}
}

void	handle_token(t_minishell *data, char *buff, int *i)
{
	if (!ft_strncmp(buff + *i, ">>&", 3))
		*i += buff_to_input(data, ">>&", Double_Great_Ampersand);
	else if (!ft_strncmp(buff + *i, ">>", 2))
		*i += buff_to_input(data, ">>", Double_Great);
	else if (!ft_strncmp(buff + *i, "<<", 2))
		*i += buff_to_input(data, "<<", Double_Less);
	else if (!ft_strncmp(buff + *i, ">&", 2))
		*i += buff_to_input(data, ">&", Great_Ampersand);
	else if (!ft_strncmp(buff + *i, "<&", 2))
		*i += buff_to_input(data, "<&", Less_Ampersand);
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
	else if (ft_is_chr_in_str("\"\'", buff[*i]))
		handle_quotes(data, buff, i);
}

void	handle_word(t_minishell *data, char *buff, int *i)
{
	char	*begin;
	char	*str;

	begin = buff + *i;
	while (ft_isalnum(buff[*i]))
		(*i)++;
	str = ft_substr(begin, 0, (size_t)(buff + *i - begin));
	buff_to_input(data, str, Word);
	free(str);
}

void	handle_forbidden_chars(t_minishell *data, char *buff, int *i)
{
	ft_printf("Invalid Chars.\n");
}

void	tokenizer(t_minishell *data, char *buff)
{
	int	i;

	i = 0;
	while (buff[i] != '\0')
	{
		while (buff[i] == ' ' || buff[i] == '\t' || buff[i] == '\n')
			i++;
		if (ft_is_chr_in_str(FORBIDDEN_CHARS, buff[i]))
		{
			handle_forbidden_chars(data, buff, &i);
			break ;
		}
		else if (ft_is_chr_in_str(TOKENS, buff[i]))
			handle_token(data, buff, &i);
		else
			handle_word(data, buff, &i);
	}
}
