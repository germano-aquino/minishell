/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:45:37 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/16 14:10:35 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_args_amount(t_node *input)
{
	int	args_amount;

	args_amount = -1;
	while (input)
	{
		if (is_connector_tok(input->tok))
			break ;
		if (input->tok == TOK_WORD)
			args_amount++;
		else if (is_redirection_tok(input->tok))
			input = input->next;
		if (input)
			input = input->next;
	}
	return (args_amount + 1);
}

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

static char	*get_cmd_path(t_minishell *data, char *cmd_base)
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

int	handle_command(t_minishell *data, t_node **input, int index, int depth)
{
	int	args_amount;
	int	i;
	int	err;

	err = 0;
	args_amount = get_args_amount(*input);
	data->cmd.args[index] = ft_calloc((args_amount + 1), sizeof(char *));
	data->cmd.cmd_path[index] = get_cmd_path(data, (*input)->data);
	data->cmd.args[index][0] = ft_strdup((*input)->data);
	data->cmd.depth[index] = depth;
	data->cmd.cmds_amount++;
	*input = (*input)->next;
	i = 0;
	while (*input && !err \
	&& !is_connector_tok((*input)->tok) && !is_parenthesis_tok((*input)->tok))
	{
		if ((*input)->tok == TOK_WORD)
		{
			data->cmd.args[index][++i] = ft_strdup((*input)->data);
			*input = (*input)->next;
		}
		else if (is_redirection_tok((*input)->tok))
			err = handle_redir(data, input, index);
	}
	return (err);
}
