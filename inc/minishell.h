/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:31:51 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/10 00:02:58 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TOKENS "<>|&$\"\'*"
# define FORBIDDEN_CHARS "\\;"
# define WORD_CHARS "=-_+/()[]{}?!~."

# define HASH_TABLE_SIZE 1031

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
	struct s_hnode	*next;
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
	int	curr_fd;
	int	fd[2];
	int	i;
}	t_workspace;

typedef struct s_command_table
{
	int			cmds_amount;
	char		**cmd_path;
	char		***args;
}	t_command_table;

typedef struct s_files
{
	t_output	which_output;
	t_input		which_input;
	char		*infile;
	char		*outfile;
}	t_files;

typedef struct s_minishell
{
	t_command_table	cmd;
	t_hash_table	env;
	int				ext_val;
	int				fd[2];
	t_files			files;
	t_node			*input;
}	t_minishell;

void	shell_loop(t_minishell *data);
void	ft_exit(t_minishell *data, const char *msg, char *buff, int end_program);

//input.c
int		buff_to_input(t_minishell *data, const char *str, t_token tok);
t_node	*create_input(const char *str, t_token tok, t_node *next, t_node *prev);
void	free_input(t_node **begin);
t_node	*get_last_input(t_node *input);

//input_utils.c
void	remove_last_input(t_node *begin);

//quotes_to_word.c
void	transform_quotes_into_word(t_node *input);

//tokens_handler.c
void	handle_word(t_minishell *data, char *buff, int *i);
void	handle_dollar(t_minishell *data, char *buff, int *i);
void	handle_single_quote(t_minishell *data, char *buff, int *i);
void	handle_double_quote(t_minishell *data, char *buff, int *i);

void	tokenizer(t_minishell *data, char *buff);

//lexer_cmd.c
int		handle_command(t_minishell *data, t_node **input, int *cmd_pos);
void	alloc_number_of_commands(t_minishell *data, int cmds_amount);
void	free_cmd_table(t_command_table *table);

//lexer_io.c
int		handle_redirect_input(t_minishell *data, t_node **input);
int		handle_redirect_output(t_minishell *data, t_node **input);
int		handle_redirect_output_append(t_minishell *data, t_node **input);
int		handle_heredoc(t_minishell *data, t_node **input);

void	invalid_syntax(t_minishell *data);

void	lexer(t_minishell *data);

//utils.c
size_t	max_size(char *s1, char *s2);
void	ft_free_2d_char_ptr(char ***ptr);
int		ft_chr_in_str(const char *str, char ch);
char	*join_str_and_free(char *str1, char *str2);

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

void	exec_cmds(t_minishell *data);

//display.c
void	display_htable(t_hash_table *table);
void	display_input(t_node *input);
void	display_cmd_table(t_command_table *cmd);

//enviroment_variables.c
void	populate_env_table(t_hash_table *table, char *envp[]);


void	free_files(t_files *files);

#endif