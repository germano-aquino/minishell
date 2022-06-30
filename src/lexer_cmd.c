/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:45:37 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/30 01:19:12 by grenato-         ###   ########.fr       */
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
	return (args_amount);
}

char	*get_cmd_path(t_minishell *data, char *cmd_base)
{
	char	**path;
	char	*temp;
	char	*cmd_path;
	int		i;

	if (!access(cmd_base, X_OK | F_OK))
		return (ft_strdup(cmd_base));
	temp = ht_search(&data->env, "PATH");
	path = ft_split(temp, ':');
	temp = ft_strjoin("/", cmd_base);
	i = -1;
	while (path[++i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], temp);
		if (!access(cmd_path, X_OK | F_OK))
		{
			free(temp);
			ft_free_2d_char_ptr(&path);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(temp);
	ft_free_2d_char_ptr(&path);
	return (NULL);
}

void	handle_command(t_minishell *data, t_node **input, int *cmd_pos)
{
	int	args_amount;
	int	i;

	args_amount = get_args_amount(*input);
	data->cmd.args[*cmd_pos] = (char **) malloc(sizeof(char *) * \
		(args_amount + 1));
	data->cmd.args[*cmd_pos][args_amount] = NULL;
	data->cmd.cmd_path[*cmd_pos] = get_cmd_path(data, (*input)->data);
	*input = (*input)->next;
	i = -1;
	while (++i < args_amount && *input != NULL)
	{
		data->cmd.args[*cmd_pos][i] = ft_strdup((*input)->data);
		*input = (*input)->next;
	}
	(*cmd_pos)++;
}

void	alloc_number_of_commands(t_minishell *data, int cmds_amount)
{
	int	i;

	data->cmd.cmds_amount = cmds_amount;
	data->cmd.cmd_path = (char **)malloc(sizeof(char *) * (cmds_amount + 1));
	data->cmd.args = (char ***)malloc(sizeof(char **) * (cmds_amount + 1));
	i = -1;
	while (++i <= cmds_amount)
	{
		data->cmd.cmd_path[i] = NULL;
		data->cmd.args[i] = NULL;
	}
}

void	free_cmd_table(t_command_table *table)
{
	int	i;

	i = -1;
	while (++i < table->cmds_amount)
	{
		if (table->cmd_path[i] != NULL)
			free(table->cmd_path[i]);
		if (table->args[i] != NULL)
			ft_free_2d_char_ptr(&table->args[i]);
	}
	if (table->args != NULL)
	{
		free(table->args);
		table->args = NULL;
	}
	if (table->cmd_path != NULL)
	{
		free(table->cmd_path);
		table->cmd_path = NULL;
	}
	table->cmds_amount = 0;
}
