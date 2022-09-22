/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 17:05:45 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/22 13:57:11 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_default_fds(int *std_fd, t_bool is_child)
{
	if (is_child)
		return ;
	dup42(std_fd[READ], STDIN);
	dup42(std_fd[WRITE], STDOUT);
}

static void	save_default_fds(int *std_fd, t_bool is_child)
{
	if (is_child)
		return ;
	std_fd[READ] = dup(STDIN);
	std_fd[WRITE] = dup(STDOUT);
}

void	exec_builtin(t_data *data, t_program *program, t_bool is_child)
{
	char	**argv;
	int		std_fd[PIPE_SIZE];

	save_default_fds(std_fd, is_child);
	if (handle_redirections(data, program, is_child) != 0)
		return (restore_default_fds(std_fd, is_child));
	argv = arg_list_to_array(program->arguments);
	if (ft_strcmp(program->path, "exit") == 0)
		builtin_exit(data, argv, is_child);
	else if (ft_strcmp(program->path, "echo") == 0)
		builtin_echo(data, argv, is_child);
	else if (ft_strcmp(program->path, "export") == 0)
		builtin_export(data, argv, is_child);
	else if (ft_strcmp(program->path, "env") == 0)
		builtin_env(data, argv, is_child);
	else if (ft_strcmp(program->path, "unset") == 0)
		builtin_unset(data, argv, is_child);
	else if (ft_strcmp(program->path, "cd") == 0)
		builtin_cd(data, argv, is_child);
	else if (ft_strcmp(program->path, "pwd") == 0)
		builtin_pwd(data, argv, is_child);
	restore_default_fds(std_fd, is_child);
}
