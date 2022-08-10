/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:31:51 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/10 15:28:35 by maolivei         ###   ########.fr       */
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
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define REGULAR_TOKENS "<>|&*"
# define PARSER_TOKENS "$\'\""
# define FORBIDDEN_CHARS "\\;"
# define WORD_CHARS "=-_+/()[]{}?!~.#@^\%`´:"

# define HASH_TABLE_SIZE 1031

typedef struct sigaction	t_sigaction;
typedef struct termios		t_termios;

typedef enum e_input
{
	Stdin,
	Infile,
	Heredoc
}	t_input;

typedef enum e_output
{
	Stdout,
	Overwrite,
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
	int				ext_val;
	t_node			*input;
}	t_minishell;

void	shell_loop(t_minishell *data);
void	ft_exit(t_minishell *data, const char *msg, char *buff, \
	int end_program);

//input.c
int		buff_to_input(t_minishell *data, const char *str, t_token tok);
t_node	*create_input(const char *str, t_token tok, t_node *next, t_node *prev);
void	free_input(t_node **begin);
t_node	*get_last_input(t_node *input);

//input_utils.c
char	*concat_and_delete_last_input(char *str, t_node *input);
void	remove_last_input(t_node *begin);

//quotes_to_word.c
void	transform_quotes_into_word(t_node *input);

//tokens_handler.c
void	handle_word(t_minishell *data, char *buff, int *i);
void	handle_dollar(t_minishell *data, char *buff, int *i);
void	handle_single_quote(t_minishell *data, char *buff, int *i);
void	handle_double_quote(t_minishell *data, char *buff, int *i);

//tokenizer.c
void	tokenizer(t_minishell *data, char *buff);
void	handle_parser(t_minishell *data, char *buff, int *i);

//dollar_handler.c
char	*get_dollar_value(t_minishell *data, char *buff, int *i);

//lexer_cmd.c
int		handle_command(t_minishell *data, t_node **input, int cmd_pos, int err);
void	alloc_number_of_commands(t_minishell *data, int cmds_amount);
void	free_cmd_table(t_command_table *table);

//lexer_io.c
int		handle_redirect_input(t_minishell *data, t_node **input, int cmd_pos);
int		handle_redirect_output(t_minishell *data, t_node **input, int cmd_pos);
int		handle_redirect_output_append(
			t_minishell *data, t_node **input, int cmd_pos);
int		handle_heredoc(t_minishell *data, t_node **input, int cmd_pos);

void	invalid_syntax(t_minishell *data);

//lexer.c
void	lexer(t_minishell *data);
int		handle_input_output(
			t_minishell *data, t_node **input, int cmd_pos, int err);

//utils.c
size_t	max_size(char *s1, char *s2);
void	ft_free_2d_char_ptr(char ***ptr);
int		ft_chr_in_str(const char *str, char ch);
char	*join_str_and_free(char *str1, char *str2);
int		max(int a, int b);
int		ft_is_number_str(const char *str);
int		ft_is_word_str(const char *str);

//hash_table_utils.c
int		hash_function(char	*key);
t_hnode	*create_item(char *key, char *value);
void	free_item(t_hnode *item);
void	ht_free(t_hash_table	*table);
char	**get_env_from_ht(t_hash_table *table);

//hash_table.c
void	ht_insert(t_hash_table *table, char *key, char *value);
char	*ht_search(t_hash_table *table, char *key);
void	ht_delete(t_hash_table *table, char *key);

//commands_execution.c
void	exec_cmds(t_minishell *data);
void	set_input_output_fd(t_minishell *data, t_workspace *vars);
void	initialize_pipes_and_pid(t_minishell *data, t_workspace *vars);

//display.c
void	display_htable(t_hash_table *table);
void	display_input(t_node *input);
void	display_cmd_table(t_command_table *cmd);

//enviroment_variables.c
void	populate_env_table(t_hash_table *table, char *envp[]);

//signal.c
void	trigger_signal(t_minishell *data, char*buff, void *handler);
void	prompt_handler(int signo);
void	heredoc_handler(int signo);
void	child_handler(int signo);
int		event(void);

//heredoc.c
int		*heredoc_interruptor(int is_interrupt);
int		ft_here_doc(t_minishell *data);

//builtins
int		is_builtin(char *cmd);
int		check_builtin(t_minishell *data, int index, t_bool is_child);
int		builtin_exit(t_minishell *data, int index, t_bool is_child);
int		builtin_echo(t_minishell *data, int index, t_bool is_child);
int		builtin_export(t_minishell *data, int index, t_bool is_child);
int		builtin_unset(t_minishell *data, int index, t_bool is_child);
int		builtin_cd(t_minishell *data, int index, t_bool is_child);
int		builtin_pwd(t_minishell *data, t_bool is_child);
int		builtin_env(t_minishell *data, t_bool is_child);
void	set_exit_value(t_minishell *data, t_bool is_child, int exit_code);

//garbage collecting
void	exit_free(t_minishell *data, t_llong exit_code);

//error handling
void	command_not_found(t_minishell *data, int index);

#endif
