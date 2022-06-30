/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 22:08:30 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/30 01:10:24 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	escape_char_and_count(char **buff, char chr, int *count)
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

int	check_unclosed_quotes(char *buff)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*buff != '\0')
	{
		if (*buff == '\'')
			escape_char_and_count(&buff, '\'', &single_quote);
		else if (*buff == '\"')
			escape_char_and_count(&buff, '\"', &double_quote);
		else
			buff++;
	}
	return (single_quote % 2 || double_quote % 2);
}

void	invalid_buff(t_minishell *data, char *buff)
{
	free_input(&data->input);
	free_cmd_table(&data->cmd);
	free(buff);
	shell_loop(data);
}

void	tokenizer(t_minishell *data, char *buff)
{
	int	i;
	int	err;

	i = 0;
	err = check_unclosed_quotes(buff);
	while (buff[i] != '\0' && !err)
	{
		while (buff[i] == ' ' || buff[i] == '\t' || buff[i] == '\n')
			i++;
		if (ft_chr_in_str(FORBIDDEN_CHARS, buff[i]))
		{
			err = 1;
			handle_forbidden_chars(data, buff, &i);
			break ;
		}
		else if (ft_chr_in_str(TOKENS, buff[i]))
			handle_token(data, buff, &i);
		else if (buff[i] != '\0')
			handle_word(data, buff, &i);
	}
	if (!err)
		transform_quotes_into_word(data->input);
	else
		invalid_buff(data, buff);
}
