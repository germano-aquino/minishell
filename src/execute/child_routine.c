/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 00:28:41 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/21 20:13:14 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_subshell(t_data *data, t_program *program)
{
	data->previous_program = NULL;
	execute(data, program->left);
	exit_free(data, g_exit_value);
}

void	child_routine(t_data *data, t_program *program)
{
	char	**argv;
	char	**envp;

	trigger_signal(FALSE, child_handler);
	handle_pipes(data->previous_program, program);
	handle_redirections(data, program, TRUE);
	if (has_path_error(program))
		exit_free(data, program->wstatus);
	if (program->is_subshell == TRUE)
		handle_subshell(data, program);
	if (is_builtin(program->path))
		exec_builtin(data, program, TRUE);
	argv = arg_list_to_array(program->args);
	if (!argv)
		exit_free(data, EXIT_SUCCESS);
	envp = get_env_from_ht(&data->env);
	execve(program->path, argv, envp);
	ft_free_matrix((void *)&argv);
	ft_free_matrix((void *)&envp);
	exit_perror(data, "execve", program->path, errno);
}
