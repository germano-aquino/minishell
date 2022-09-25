/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:31:51 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/25 18:48:18 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE
# define _POSIX_SOURCE

# include "internals.h"

/* Minishell */
int			minishell(char **envp);

/* Prompt */
void		shell_loop(t_data *data);
void		redisplay_prompt(t_data *data, char *msg, char *buff, int status);
char		*get_prompt_info(t_hash_table *env);
char		*exit_value_to_string(int status);

/* Input */
int			buff_to_input(t_data *data, char *str, t_token tok);
void		free_input(t_node **begin);
char		*concat_and_delete_last_input(char *str, t_node **input);
t_node		*get_last_input(t_node *input);
t_node		*create_input(char *str, t_token tok, t_node *next, t_node *prev);

/* Hashtable */
int			hash_function(char *key);
void		free_item(t_hnode *item);
void		ht_free(t_hash_table *table);
void		ht_insert(t_hash_table *table, char *key, char *value);
void		ht_delete(t_hash_table *table, char *key);
void		populate_env_table(t_hash_table *table, char **envp);
char		*ht_search(t_hash_table *table, char *key);
char		**get_env_from_ht(t_hash_table *table);
t_hnode		*create_item(char *key, char *value);

/* Heredoc */
int			*init_heredoc_signal(void);
int			*heredoc_interruptor(int is_interrupt);
void		ft_here_doc(t_data *data, char *delimiter);
void		heredoc_handler(int sig);

/* Lexer */
void		lexer(t_data *data);
void		handle_subsh_tok(t_data *data, t_program *program, t_node **input);
void		handle_word_tok(t_data *data, t_program *program, t_node **input);
void		handle_redir_tok(t_data *data, t_program *program, t_node **input);
void		handle_connector(t_data *data, t_program *program, t_node **input);
t_program	*create_program(t_data *data, t_node **input, t_bool subshell);

/* Tokenizer */
void		tokenizer(t_data *data, char *buff);
void		handle_parser(t_data *data, char *buff, size_t *i);
void		wildcard_expansion(t_data *data);
char		*handle_dollar(t_data *data, char *buff, size_t *i);
char		**get_objects_in_current_directory(char *exp);
t_bool		filter_is_obj_suffix(char *obj, char *filter);

/* Error handling */
void		exit_perror(t_data *data, char *cmd, char *perr, int exit_code);
void		syntax_error(t_data *data, t_node *input);
t_bool		print_error_msg(char *cmd, char *msg);
t_bool		print_perror_msg(char *cmd, char *perror_msg);

/* Utils */
void		initialize_minishell(t_data *data);
void		dup42(int fd_1, int fd_2);
t_bool		is_number_str(const char *str);
t_bool		is_word_str(const char *str);
t_bool		is_path(char *str);
t_bool		is_directory(char *path);
t_bool		is_connector_tok(t_token token);
t_bool		is_redirection_tok(t_token token);
t_bool		is_parenthesis_tok(t_token token);
t_bool		has_path_error(t_program *program);

/* Garbage collecting */
void		exit_free(t_data *data, int exit_code);
void		free_minishell(t_data *data);
void		free_programs(t_program **programs);
void		clear_program_file(void *content);

/* Signal handling */
int			event(void);
void		trigger_signal(t_bool ignore_sigquit, void *handler);
void		prompt_handler(int sig, t_hash_table *env);
void		cmd_handler(int sig);
void		child_handler(int sig);
void		handle_dead_child(t_program *program, pid_t process_id, int status);

/* Command execution */
void		execute(t_data *data, t_program *root);
void		wait_child(t_data *data);
void		wait_conditional_child(t_program *program);
void		set_child_wstatus(t_program *program, pid_t process_id, int status);
void		skip_pipeline(t_program **previous_program, t_program **program);
void		parent_routine(t_data *data, t_program *program);
void		child_routine(t_data *data, t_program *program);
void		handle_pipes(t_program *previous_program, t_program *program);
char		**arg_list_to_array(t_list *arguments);
t_bool		handle_input_redir(t_data *data, t_io_file *file, t_bool is_child);
t_bool		handle_output_redir(t_data *data, t_io_file *file, t_bool is_child);
t_bool		has_conditional_error(t_program *previous_program);
t_bool		handle_redirections(
				t_data *data, t_program *program, t_bool is_child);

/* Builtins */
t_bool		builtin_cd(t_data *data, char **argv, t_bool is_child);
t_bool		builtin_echo(t_data *data, char **argv, t_bool is_child);
t_bool		builtin_env(t_data *data, char **argv, t_bool is_child);
t_bool		builtin_exit(t_data *data, char **argv, t_bool is_child);
t_bool		builtin_export(t_data *data, char **argv, t_bool is_child);
t_bool		builtin_pwd(t_data *data, char **argv, t_bool is_child);
t_bool		builtin_unset(t_data *data, char **argv, t_bool is_child);

/* Builtin utils */
void		exec_builtin(t_data *data, t_program *program, t_bool is_child);
void		set_exit_value(t_data *data, t_bool is_child, int exit_code);
t_bool		is_builtin(char *cmd);

#endif /* MINISHELL_H */
