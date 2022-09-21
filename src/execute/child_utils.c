/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 01:12:38 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 03:28:52 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arg_list_to_array(t_list *arguments)
{
	const size_t	list_size = ft_lstsize(arguments);
	char			**argv;
	char			*current_argument;
	size_t			index;

	if (list_size < 1)
		return (NULL);
	argv = (char **)ft_calloc((list_size + 1), sizeof(char *));
	index = 0;
	while (index < list_size)
	{
		current_argument = (char *)arguments->content;
		argv[index] = ft_strdup(current_argument);
		arguments = arguments->next;
		++index;
	}
	return (argv);
}

t_bool	handle_output_redir(t_data *data, t_io_file *file, t_bool is_child)
{
	int	fd;

	if (file->io_type == IO_TRUNC)
		fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		if (is_child)
			exit_perror(data, NULL, file->filename, EXIT_FAILURE);
		print_perror_msg(NULL, file->filename);
		g_exit_value = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	dup42(fd, STDOUT);
	return (EXIT_SUCCESS);
}

t_bool	handle_input_redir(t_data *data, t_io_file *file, t_bool is_child)
{
	int	fd;

	fd = open(file->filename, O_RDONLY);
	if (fd < 0)
	{
		if (is_child)
			exit_perror(data, NULL, file->filename, EXIT_FAILURE);
		print_perror_msg(NULL, file->filename);
		g_exit_value = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	dup42(fd, STDIN);
	return (EXIT_SUCCESS);
}

t_bool	handle_redirections(t_data *data, t_program *program, t_bool is_child)
{
	t_list		*io_list;
	t_io_file	*file;

	io_list = program->io_files;
	while (io_list)
	{
		file = (t_io_file *)io_list->content;
		if (file->io_type == IO_INFILE || file->io_type == IO_HEREDOC)
		{
			if (handle_input_redir(data, file, is_child) != 0)
				return (EXIT_FAILURE);
		}
		else
		{
			if (handle_output_redir(data, file, is_child) != 0)
				return (EXIT_FAILURE);
		}
		io_list = io_list->next;
	}
	dup42(data->fd_err, STDERR);
	return (EXIT_SUCCESS);
}

void	handle_pipes(t_program *previous_program, t_program *program)
{
	if (previous_program && previous_program->connector == PIPE)
	{
		dup42(previous_program->pipe_fd[IN], STDIN);
		close(previous_program->pipe_fd[OUT]);
	}
	if (program->connector == PIPE)
	{
		dup42(program->pipe_fd[OUT], STDOUT);
		close(program->pipe_fd[IN]);
	}
}
