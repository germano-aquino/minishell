/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:45:37 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/20 19:52:04 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_args_amount(t_node *input)
{
	int	args_amount;

	args_amount = -1;
	while (input != NULL && input->tok == Word)
	{
		args_amount++;
		input = input->next;
	}
	return (args_amount + 1);
}

char	*find_absolute_cmd_path(char *cmd_base, char **path)
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (path[++i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], cmd_base);
		if (!access(cmd_path, X_OK | F_OK))
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

char	*get_cmd_path(t_minishell *data, char *cmd_base)
{
	char	**path;
	char	*temp;
	char	*cmd_path;

	temp = ht_search(&data->env, "PATH");
	path = ft_split(temp, ':');
	temp = ft_strjoin("/", cmd_base);
	if (!access(cmd_base, X_OK | F_OK) || is_builtin(cmd_base))
		cmd_path = ft_strdup(cmd_base);
	else
		cmd_path = find_absolute_cmd_path(temp, path);
	free(temp);
	ft_free_2d_char_ptr(&path);
	return (cmd_path);
}

int	handle_command(t_minishell *data, t_node **input, int *cmd_pos)
{
	int	args_amount;
	int	i;

	args_amount = get_args_amount(*input);
	data->cmd.args[*cmd_pos] = (char **) malloc(sizeof(char *) * \
		(args_amount + 2));
	data->cmd.args[*cmd_pos][args_amount] = NULL;
	data->cmd.cmd_path[*cmd_pos] = get_cmd_path(data, (*input)->data);
	data->cmd.args[*cmd_pos][0] = ft_strdup((*input)->data);
	*input = (*input)->next;
	i = 0;
	while (++i < args_amount && *input != NULL)
	{
		data->cmd.args[*cmd_pos][i] = ft_strdup((*input)->data);
		*input = (*input)->next;
	}
	(*cmd_pos)++;
	return (0);
}

void	alloc_number_of_commands(t_minishell *data, int cmds_amount)
{
	data->cmd.cmds_amount = cmds_amount;
	data->cmd.cmd_path = (char **)ft_calloc((cmds_amount + 1), sizeof(char *));
	data->cmd.args = (char ***)ft_calloc((cmds_amount + 1), sizeof(char **));
}
