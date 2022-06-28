/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:26:05 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/28 02:17:39 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_redirect_input(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if ((*input)->tok == Word)
	{
		if (!access((*input)->data, F_OK | R_OK))
			data->fd[0] = open((*input)->data, O_RDONLY);
		*input = (*input)->next;
	}
	else
		ft_printf("syntax error near unexpected token \'<\'\n");
}

void	handle_redirect_output(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if ((*input)->tok == Word)
	{
		if (access((*input)->data, F_OK | W_OK) == -1)
			unlink((*input)->data);
		data->fd[1] = open((*input)->data, O_CREAT | O_WRONLY, 0666);
		*input = (*input)->next;
	}
	else
		ft_printf("syntax error near unexpected token \'>\'\n");
}

void	handle_redirect_output_append(t_minishell *data, t_node **input)
{
	*input = (*input)->next;
	if ((*input)->tok == Word)
	{
		if (!access((*input)->data, F_OK))
			data->fd[1] = open((*input)->data, O_APPEND | O_WRONLY);
		else
			data->fd[1] = open((*input)->data, O_CREAT | O_WRONLY, 0666);
		*input = (*input)->next;
	}
	else
		ft_printf("syntax error near unexpected token \'>>\'\n");
}

int	get_pipes_amount(t_node *input)
{
	int	pipes_amount;

	pipes_amount = 0;
	while (input != NULL)
	{
		if (input->tok == Pipe)
			pipes_amount++;
		input = input->next;
	}
	return (pipes_amount);
}

void	alloc_number_of_commands(t_minishell *data)
{
	int	cmds_amount;

	cmds_amount = data->pipes_amount + 1;
	data->cmd.cmd_path = (char **)malloc(sizeof(char *) * (cmds_amount + 1));
	data->cmd.args = (char ***)malloc(sizeof(char **) * (cmds_amount + 1));
	data->cmd.cmd_path[cmds_amount] = NULL;
	data->cmd.args[cmds_amount] = NULL;
}

void	handle_pipe(t_node **input)
{
	*input = (*input)->next;
	if ((*input)->tok != Word)
		ft_printf("syntax error near unexpected token \'|\'\n");
}

int	get_args_amount(t_node *input)
{
	//TODO: args with quotes!
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
	temp = ht_search(data->env, "PATH");
	path = ft_split(temp, ':');
	temp = ft_strjoin("/", cmd_base);
	i = -1;
	while (path[++i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], temp);
		if (!access(cmd_path, X_OK | F_OK))
		{
			ft_free_2d_char_ptr(&path);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_free_2d_char_ptr(&path);
	return (NULL);
}

void	handle_command(t_minishell *data, t_node **input, int *cmd_pos)
{
	int	args_amount;
	int	i;

	args_amount = get_args_amount(*input);
	data->cmd.args[*cmd_pos] = (char **) malloc(sizeof(char *) * (args_amount + 1));
	data->cmd.args[*cmd_pos][args_amount] = NULL;
	data->cmd.cmd_path[*cmd_pos] = get_cmd_path(data, (*input)->data);
	*input = (*input)->next;
	i = -1;
	while (++i < args_amount && *input != NULL)
	{
		data->cmd.args[*cmd_pos][i] = ft_strdup((*input)->data);
		*input = (*input)->next;
	}
	*input = (*input)->next;
}

void	lexer(t_minishell *data)
{
	t_node	*input;
	int		cmd_pos;

	cmd_pos = 0;
	input = &data->input;
	data->pipes_amount = get_pipes_amount(input);
	alloc_number_of_commands(data);
	while (input != NULL)
	{
		if (input->tok == Less)
			handle_redirect_input(data, &input);
		else if (input->tok == Great)
			handle_redirect_output(data, &input);
		else if (input->tok == Double_Great)
			handle_redirect_output_append(data, &input);
		else if(input->tok == Pipe)
			handle_pipe(&input);
		else if(input->tok == Word)
			handle_command(data, &input, &cmd_pos);
	}
}