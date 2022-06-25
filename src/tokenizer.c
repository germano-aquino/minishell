/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:08:30 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/24 23:23:25 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_dollar(t_minishell *data, char *buff, int *i)
{
	size_t	begin;
	char	*key;
	char	*env_var;

	begin = (size_t) ++(*i);
	env_var = NULL;
	if (ft_isalpha(buff[*i]) || buff[*i] == '_')
	{
		while (ft_isalnum(buff[*i]) || buff[*i] == '_')
			(*i)++;
		key = ft_substr(buff, begin, (size_t)*i - begin);
		env_var = ht_search(&data->env, key);
		free(key);
	}
	buff_to_input(data, env_var, Dollar);
}

void	handle_single_quote(t_minishell *data, char *buff, int *i)
{
	size_t	begin;
	char	*str;

	begin = (size_t) (*i)++;
	while (buff[*i] != '\'')
		(*i)++;
	(*i)++;
	str = ft_substr(buff, begin, (size_t)*i - begin);
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
		if (buff[*i] == '$' || buff[*i] == '\'')
		{
			str = ft_substr(buff, begin, (size_t)*i - begin);
			buff_to_input(data, str, Double_Quote);
			if (buff[*i] == '$')
				handle_dollar(data, buff, i);
			if (buff[*i] == '\'')
				handle_single_quote(data, buff, i);
			begin = (size_t)*i;
			free(str);
		}
		else
			(*i)++;
	}
	(*i)++;
	str = ft_substr(buff, begin, (size_t)*i - begin);
	buff_to_input(data, str, Double_Quote);
	free(str);
}

void	handle_token(t_minishell *data, char *buff, int *i)
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
	else if (ft_chr_in_str("\'", buff[*i]))
		handle_single_quote(data, buff, i);
	else if (ft_chr_in_str("\"", buff[*i]))
		handle_double_quote(data, buff, i);
	else if (!strncmp(buff + *i, "$", 1))
		handle_dollar(data, buff, i);
}

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

void	tokenizer(t_minishell *data, char *buff)
{
	int	i;

	i = 0;
	while (buff[i] != '\0')
	{
		while (buff[i] == ' ' || buff[i] == '\t' || buff[i] == '\n')
			i++;
		if (ft_chr_in_str(FORBIDDEN_CHARS, buff[i]))
		{
			handle_forbidden_chars(data, buff, &i);
			break ;
		}
		else if (ft_chr_in_str(TOKENS, buff[i]))
			handle_token(data, buff, &i);
		else
			handle_word(data, buff, &i);
	}
}
