/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:45:49 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/05 00:23:44 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_here_doc(t_minishell *data)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_exit(data, "cannot create pipe.\n", NULL, 0);
	while (1)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO, 0);
		if (!ft_strncmp(line, data->files.infile, ft_strlen(line) - 1) \
			&& line[ft_strlen(line) - 1] == '\n')
		{
			close(fd[1]);
			free(line);
			line = get_next_line(STDIN_FILENO, 1);
			return (fd[0]);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	return (0);
}

void	set_input_output_fd(t_minishell *data)
{
	if (data->files.which_input == Stdin)
		data->fd[0] = dup(STDIN_FILENO);
	else if (data->files.which_input == Infile)
		data->fd[0] = open(data->files.infile, O_RDONLY);
	else if (data->files.which_input == Heredoc)
		data->fd[0] = ft_here_doc(data);
	if (data->files.which_output == Stdout)
		data->fd[1] = dup(STDOUT_FILENO);
	else if (data->files.which_output == Overwrite)
		data->fd[1] = open(data->files.outfile, O_CREAT | O_WRONLY, 0666);
	else
		data->fd[1] = open(data->files.outfile, O_CREAT | O_APPEND \
		| O_WRONLY, 0666);
	data->files.which_input = Stdin;
	data->files.which_output = Stdout;
}

void	child_task(t_minishell *data, t_workspace *vars)
{
	dup2(vars->curr_fd, STDIN_FILENO);
	close(vars->curr_fd);
	close(vars->fd[0]);
	if (vars->i == data->cmd.cmds_amount - 1)
	{
		close(vars->fd[1]);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
	}
	else
	{
		dup2(vars->fd[1], STDOUT_FILENO);
		close(vars->fd[1]);
	}
	if (execve(data->cmd.cmd_path[vars->i], \
		data->cmd.args[vars->i], NULL) == -1)
		ft_exit(data, "cannot create pipe.\n", NULL, 0);
}

void	exec_cmd(t_minishell *data, \
			t_workspace *vars)
{
	int	pid;

	if (pipe(vars->fd) == -1)
		ft_exit(data, "cannot create pipe.\n", NULL, 0);
	if (vars->curr_fd == -1)
		vars->curr_fd = vars->fd[0];
	pid = fork();
	if (pid == 0)
		child_task(data, vars);
	else
	{
		close(vars->curr_fd);
		dup2(vars->fd[0], vars->curr_fd);
		close(vars->fd[0]);
		close(vars->fd[1]);
		if (vars->i == data->cmd.cmds_amount - 1)
			waitpid(pid, &data->ext_val, 0);
	}
}

void	exec_cmds(t_minishell *data)
{
	t_workspace	vars;

	vars.i = -1;
	set_input_output_fd(data);
	vars.curr_fd = data->fd[0];
	while (++vars.i < data->cmd.cmds_amount)
	{
		if (data->cmd.cmd_path[vars.i] != NULL && \
			!(vars.i == (data->cmd.cmds_amount - 1) && data->fd[1] == -1))
			exec_cmd(data, &vars);
	}
	close(vars.curr_fd);
	close(data->fd[1]);
	data->ext_val = WEXITSTATUS(data->ext_val);
}
