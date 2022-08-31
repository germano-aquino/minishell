/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:31:51 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/31 12:44:00 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE
# define _POSIX_SOURCE

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Parsing */
# define REGULAR_TOKENS "<>|&"
# define PARSER_TOKENS "$'\""

# define ERR_QUOTES "there are unclosed quotes"
# define ERR_SYNTAX "syntax error near unexpected token "
# define TRUNC_STR "`>'"
# define APPEND_STR "`>>'"
# define INPUT_STR "`<'"
# define HEREDOC_STR "`<<'"
# define PIPE_STR "`|'"
# define NEWLINE_STR "`newline'"

# define SQUOTE '\''	/* Single quote character */
# define DQUOTE '"'		/* Double quote character */
# define DOLLAR '$'		/* Dollar sign (env variable expansion) character */
# define TILDE '~'		/* Tilde expansion character */

/* Temporary files */
# define TMP_HEREDOC_PATH "/tmp/mini_heredoc"	/* Heredoc temporary file */
# define TMP_ERROR_PATH "/tmp/mini_error"		/* STDERR temporary file */

/* Pipe */
# define IN 0			/* Pipe read end */
# define OUT 1			/* Pipe write end */
# define PIPE_SIZE 2	/* Pipe total size */

/* Exit code */
# define EXIT_BAD_USAGE 2			/* Builtin misuse, syntax error */
# define EXIT_NOT_EXECUTABLE 126	/* Permission denied, Is a directory */
# define EXIT_NOT_FOUND 127			/* Command not found */
# define EXIT_SIGINT 130			/* Interrupt program, normally Ctrl+C */
# define EXIT_SIGQUIT 131			/* Interrupt program, normally Ctrl+\ */

/* Hashtable */
# define HASH_TABLE_SIZE 1031		/* Hashtable total size */
# define HASH_RIGHT_OFFSET 24		/* Right bit-shifting offset */
# define HASH_LEFT_OFFSET 4			/* Left bit-shifting offset */
# define HASH_LIMITER 0xf0000000	/* Hashing limiter */

extern int					g_exit_value;

typedef struct sigaction	t_sigaction;
typedef struct stat			t_stat;
typedef struct dirent		t_dirent;

typedef enum e_input
{
	Stdin,
	Infile,
	Heredoc
}	t_input;

typedef enum e_output
{
	Stdout,
	Truncate,
	Append
}	t_output;

typedef struct s_files
{
	t_output	which_output;
	t_input		which_input;
	char		*infile;
	char		*outfile;
}	t_files;

typedef enum e_token
{
	Word,
	File,
	Dollar,
	Pipe,
	Double_Pipe,
	Great,
	Double_Great,
	Less,
	Double_Less,
	Ampersand,
	Double_Ampersand,
	Quote,
	Double_Quote,
	Wildcard
}	t_token;

typedef struct s_hnode
{
	char				*key;
	char				*value;
	struct s_hnode		*next;
}	t_hnode;

typedef struct s_hash_table
{
	t_hnode	*item[HASH_TABLE_SIZE];
}	t_hash_table;

typedef struct s_node
{
	char			*data;
	t_token			tok;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_workspace
{
	int		**fd;
	pid_t	*pid;
}	t_workspace;

typedef struct s_command_table
{
	int			cmds_amount;
	char		**cmd_path;
	char		***args;
	t_files		*files;
}	t_command_table;

typedef struct s_minishell
{
	t_command_table	cmd;
	t_hash_table	env;
	t_node			*input;
	int				child_exit_code;
	int				fd_err;
}	t_minishell;

//init.c
void	ft_open_fd_err(t_minishell *data);

//free.c
void	ft_close_fd_err(t_minishell *data);

void	shell_loop(t_minishell *data);
void	redisplay_prompt(t_minishell *data, char *msg, char *buff, int status);
void	ft_init(t_minishell *data);
int		minishell(char **envp);

//input.c
t_node	*create_input(const char *str, t_token tok, t_node *next, t_node *prev);
t_node	*get_last_input(t_node *input);
void	free_input(t_node **begin);
int		buff_to_input(t_minishell *data, const char *str, t_token tok);

//input_utils.c
char	*concat_and_delete_last_input(char *str, t_node **input);

//quotes_to_word.c
void	transform_quotes_into_word(t_node *input);

//tokens_handler.c
char	*handle_dollar(t_minishell *data, char *buff, size_t *i);

//tokenizer.c
void	tokenizer(t_minishell *data, char *buff);
void	handle_parser(t_minishell *data, char *buff, size_t *i);

//wildcard_dir_objs.c
int		amount_objs_in_current_dir(t_bool begin_with_dot);
char	**get_objects_in_current_directory(char *exp);
t_bool	filter_is_obj_suffix(char *obj, char *filter);

//wildcard_handler.c
void	wildcard_expansion(t_minishell *data);

//lexer_cmd.c
void	alloc_number_of_commands(t_minishell *data, int cmds_amount);
void	free_cmd_table(t_command_table *table, t_node *input);
int		handle_command(t_minishell *data, t_node **input, int cmd_pos, int err);

//lexer.c
t_bool	validate_path(t_minishell *data, char *path, int cmd_pos);
void	lexer(t_minishell *data);
int		handle_redir(t_minishell *data, t_node **input, int cmd_pos, int err);

t_bool	is_path(char *str);
t_bool	is_directory(char *path);

//utils.c
t_bool	ft_chr_in_str(const char *str, char ch);
t_bool	ft_is_number_str(const char *str);
t_bool	ft_is_word_str(const char *str);
int		get_pipes_amount(t_node *input);

//hash_table_utils.c
t_hnode	*create_item(char *key, char *value);
char	**get_env_from_ht(t_hash_table *table);
void	free_item(t_hnode *item);
void	ht_free(t_hash_table *table);
int		hash_function(char *key);

//hash_table.c
char	*ht_search(t_hash_table *table, char *key);
void	ht_insert(t_hash_table *table, char *key, char *value);
void	ht_delete(t_hash_table *table, char *key);

//commands_execution.c
void	execute_forks(t_minishell *data);
void	initialize_pipes_and_pid(t_minishell *data, t_workspace *vars);
int		check_builtin(t_minishell *data, int index, t_bool is_child);
int		exec_builtin(t_minishell *data, int index, t_bool is_child);

//display.c
void	display_htable(t_hash_table *table);
void	display_input(t_node *input);
void	display_cmd_table(t_command_table *cmd);

//enviroment_variables.c
void	populate_env_table(t_hash_table *table, char **envp);

//signal.c
void	trigger_signal(t_bool ignore_sigquit, void *handler);
void	prompt_handler(int sig);
void	heredoc_handler(int sig);
void	cmd_handler(int sig);
void	child_handler(int sig);

//heredoc.c
void	ft_here_doc(t_minishell *data, char *delimiter);
int		*heredoc_interruptor(int is_interrupt);
int		*init_heredoc_signal(void);
int		event(void);

//builtins
t_bool	is_builtin(char *cmd);
void	set_exit_value(t_minishell *data, t_bool is_child, int exit_code);
void	set_io_builtin(t_minishell *data, t_workspace *vars, int *std_io);
void	reset_io_builtin(t_workspace *vars, int *std_io);
int		check_builtin(t_minishell *data, int index, t_bool is_child);
int		builtin_exit(t_minishell *data, int index, t_bool is_child);
int		builtin_echo(t_minishell *data, int index, t_bool is_child);
int		builtin_export(t_minishell *data, int index, t_bool is_child);
int		builtin_unset(t_minishell *data, int index, t_bool is_child);
int		builtin_cd(t_minishell *data, int index, t_bool is_child);
int		builtin_pwd(t_minishell *data, t_bool is_child);
int		builtin_env(t_minishell *data, t_bool is_child);

//garbage collecting
void	exit_free(t_minishell *data, t_llong exit_code);
void	free_minishell(t_minishell *data);

//error handling
t_bool	print_error_msg(char *cmd, char *msg);
t_bool	print_perror_msg(char *cmd, char *perror_msg);
void	exit_perror(t_minishell *data, char *cmd, char *perr, int exit_code);
void	syntax_error(t_minishell *data, t_node *input);
void	print_error_file(t_minishell *data);

#endif
