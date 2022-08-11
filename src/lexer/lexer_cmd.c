/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:45:37 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/10 21:59:42 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_args_amount(t_node *input)
{
	int	args_amount;

	args_amount = -1;
	while (input != NULL)
	{
		if (input->tok == Pipe)
			break ;
		if (input->tok == Word)
			args_amount++;
		else if (input->tok == Less || input->tok == Double_Less
			|| input->tok == Great || input->tok == Double_Great)
			input = input->next;
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

	if (!access(cmd_base, X_OK | F_OK) || is_builtin(cmd_base))
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
		ft_free_2d_char_ptr(&path);
	}
	return (cmd_path);
}

int	handle_command(t_minishell *data, t_node **input, int cmd_pos, int err)
{
	int	args_amount;
	int	i;

	args_amount = get_args_amount(*input);
	data->cmd.args[cmd_pos] = (char **) malloc(sizeof(char *) * \
		(args_amount + 2));
	data->cmd.args[cmd_pos][args_amount] = NULL;
	data->cmd.cmd_path[cmd_pos] = get_cmd_path(data, (*input)->data);
	data->cmd.args[cmd_pos][0] = ft_strdup((*input)->data);
	*input = (*input)->next;
	i = 0;
	while (++i < args_amount && *input != NULL && !err)
	{
		if ((*input)->tok == Word)
		{
			data->cmd.args[cmd_pos][i] = ft_strdup((*input)->data);
			*input = (*input)->next;
		}
		else
		{
			err = handle_input_output(data, input, cmd_pos, err);
			--i;
		}
	}
	return (err);
}

void	alloc_number_of_commands(t_minishell *data, int cmds_amount)
{
	data->cmd.cmds_amount = cmds_amount;
	data->cmd.cmd_path = (char **)ft_calloc((cmds_amount + 1), sizeof(char *));
	data->cmd.args = (char ***)ft_calloc((cmds_amount + 1), sizeof(char **));
	data->cmd.files = (t_files *)ft_calloc((cmds_amount + 1), sizeof(t_files));
}
