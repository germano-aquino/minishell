/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:31:51 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/15 21:30:36 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE
# define _POSIX_SOURCE

# include "internals.h"

/* Display (REMOVE LATER) */
void	display_input(t_node *input);
void	display_htable(t_hash_table *table);
void	display_cmd_table(t_command_table *cmd);

/* Minishell */
int		minishell(char **envp);

/* Prompt */
void	shell_loop(t_minishell *data);
void	redisplay_prompt(t_minishell *data, char *msg, char *buff, int status);
char	*get_prompt_info(t_hash_table *env);

/* Input */
t_node	*create_input(const char *str, t_token tok, t_node *next, t_node *prev);
t_node	*get_last_input(t_node *input);
char	*concat_and_delete_last_input(char *str, t_node **input);
void	free_input(t_node **begin);
int		buff_to_input(t_minishell *data, const char *str, t_token tok);

/* Hashtable */
t_hnode	*create_item(char *key, char *value);
char	**get_env_from_ht(t_hash_table *table);
char	*ht_search(t_hash_table *table, char *key);
void	free_item(t_hnode *item);
void	ht_free(t_hash_table *table);
void	ht_insert(t_hash_table *table, char *key, char *value);
void	ht_delete(t_hash_table *table, char *key);
void	populate_env_table(t_hash_table *table, char **envp);
int		hash_function(char *key);

/* Heredoc */
void	ft_here_doc(t_minishell *data, char *delimiter);
void	heredoc_handler(int sig);
int		*heredoc_interruptor(int is_interrupt);
int		*init_heredoc_signal(void);

/* Lexer */
void	lexer(t_minishell *data);
int		handle_redir(t_minishell *data, t_node **input, int cmd_pos, int err);
int		handle_command(t_minishell *data, t_node **input, int cmd_pos, int err);

/* Tokenizer */
void	tokenizer(t_minishell *data, char *buff);
void	handle_parser(t_minishell *data, char *buff, size_t *i);
void	wildcard_expansion(t_minishell *data);
char	*handle_dollar(t_minishell *data, char *buff, size_t *i);
char	**get_objects_in_current_directory(char *exp);
t_bool	filter_is_obj_suffix(char *obj, char *filter);

/* Error handling */
t_bool	print_error_msg(char *cmd, char *msg);
t_bool	print_perror_msg(char *cmd, char *perror_msg);
void	exit_perror(t_minishell *data, char *cmd, char *perr, int exit_code);
void	open_fd_err(t_minishell *data);
void	close_fd_err(t_minishell *data);
void	syntax_error(t_minishell *data, t_node *input);
void	print_error_file(t_minishell *data);

/* Utils */
t_bool	is_number_str(const char *str);
t_bool	is_word_str(const char *str);
t_bool	is_path(char *str);
t_bool	is_directory(char *path);
t_bool	is_connector_tok(t_token token);
t_bool	is_redirection_tok(t_token token);
t_bool	has_path_error(t_minishell *data, t_workspace *vars, char *cmd, int i);
int		get_connectors_amount(t_node *input);
void	ft_init(t_minishell *data);
void	dup42(int fd_1, int fd_2);

/* Garbage collecting */
void	free_cmd_table(t_command_table *table, t_node *input);
void	exit_free(t_minishell *data, t_llong exit_code);
void	free_minishell(t_minishell *data);

/* Signal handling */
void	trigger_signal(t_bool ignore_sigquit, void *handler);
void	prompt_handler(int sig, t_hash_table *env);
void	cmd_handler(int sig);
void	child_handler(int sig);
void	handle_dead_child(t_workspace *vars, pid_t process_id, int status);
int		event(void);

/* Command execution */
void	execute(t_minishell *data);
void	initialize_workspace(t_minishell *data, t_workspace *vars);
void	set_exit_value(t_minishell *data, t_bool is_child, int exit_code);
void	set_child_wstatus(t_workspace *vars, pid_t process_id, int status);
void	wait_child(t_workspace *vars, int cmds_amount, int should_wait);
void	set_child_wstatus(t_workspace *vars, pid_t process_id, int status);
void	skip_pipeline(t_minishell *data, t_workspace *vars, int *index);
void	wait_conditional_child(t_workspace *vars, int index);
t_bool	has_conditional_error(t_minishell *data, t_workspace *vars, int index);

/* Builtins */
int		builtin_cd(t_minishell *data, int index, t_bool is_child);
int		builtin_echo(t_minishell *data, int index, t_bool is_child);
int		builtin_env(t_minishell *data, t_bool is_child);
int		builtin_exit(t_minishell *data, int index, t_bool is_child);
int		builtin_export(t_minishell *data, int index, t_bool is_child);
int		builtin_pwd(t_minishell *data, t_bool is_child);
int		builtin_unset(t_minishell *data, int index, t_bool is_child);

/* Builtin utils */
t_bool	is_builtin(char *cmd);
void	set_io_builtin(t_minishell *data, t_workspace *vars, int *std_io);
void	reset_io_builtin(t_workspace *vars, int *std_io);
int		check_builtin(t_minishell *data, int index, t_bool is_child);
int		exec_builtin(t_minishell *data, int index, t_bool is_child);

#endif
