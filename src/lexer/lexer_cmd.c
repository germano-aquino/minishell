/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:45:37 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/21 21:22:04 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_absolute_cmd_path(char *cmd_base, char **path)
{
	int		i;
	char	*cmd_path;

	if (!cmd_base[1])
		return (NULL);
	i = -1;
	while (path[++i])
	{
		cmd_path = ft_strjoin(path[i], cmd_base);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

static char	*get_cmd_path(t_data *data, char *cmd_base)
{
	char	**path;
	char	*temp;
	char	*cmd_path;

	if (is_builtin(cmd_base) || is_path(cmd_base))
		cmd_path = ft_strdup(cmd_base);
	else
	{
		temp = ht_search(&data->env, "PATH");
		if (!temp)
			return (NULL);
		path = ft_split(temp, ':');
		temp = ft_strjoin("/", cmd_base);
		cmd_path = find_absolute_cmd_path(temp, path);
		free(temp);
		ft_free_matrix((void *)&path);
	}
	return (cmd_path);
}

void	handle_word_tok(t_data *data, t_program *program, t_node **input)
{
	t_list	*new_argument;

	if ((*input)->next && (*input)->next->tok == TOK_OPEN_PARENTHESIS)
	{
		free_programs(&program);
		syntax_error(data, (*input)->next);
	}
	new_argument = ft_lstnew(ft_strdup((*input)->data));
	if (!program->arguments)
	{
		program->path = get_cmd_path(data, (*input)->data);
		program->arguments = new_argument;
	}
	else
		ft_lstadd_back(&program->arguments, new_argument);
	(*input) = (*input)->next;
}
