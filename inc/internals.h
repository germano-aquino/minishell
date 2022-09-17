/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:54:38 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/17 02:35:05 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNALS_H
# define INTERNALS_H

# include "../libft/libft.h" /* libft, ft_* */

/* External libraries */
/* access, chdir, close, dup2, dup, execve, exit, fork, pipe, read, unlink */
# include <unistd.h>
# include <fcntl.h>				/* open */
# include <stdio.h>				/* printf, perror */
# include <dirent.h>			/* readdir */
# include <signal.h>			/* sigaction, sigemptyset */
# include <sys/types.h>			/* opendir, closedir */
# include <sys/wait.h>			/* wait, waitpid */
# include <sys/stat.h>			/* stat */
# include <readline/readline.h>	/* readline, rl_* */
# include <readline/history.h>	/* readline, add_history, rl_* */
/* stdlib for getenv */

/* Parsing */
# define REGULAR_TOKENS "<>|&()"
# define PARSER_TOKENS "$'\""

# define ERR_QUOTES "there are unclosed quotes"
# define ERR_PARENTHESIS "there are unclosed parenthesis"
# define ERR_SYNTAX "syntax error near unexpected token "
# define TRUNC_STR "`>'"
# define APPEND_STR "`>>'"
# define INPUT_STR "`<'"
# define HEREDOC_STR "`<<'"
# define PIPE_STR "`|'"
# define OR_STR "`||'"
# define AND_STR "`&&'"
# define OPEN_STR "`('"
# define CLOSE_STR "`)'"
# define NEWLINE_STR "`newline'"

# define OPEN_PARENTHESIS '('	/* Parenthesis opening character */
# define CLOSE_PARENTHESIS ')'	/* Parenthesis closing character */
# define SQUOTE '\''			/* Single quote character */
# define DQUOTE '"'				/* Double quote character */
# define DOLLAR '$'				/* Dollar sign (variable expansion) character */
# define TILDE '~'				/* Tilde expansion character */

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
# define EXIT_OFFSET 128			/* Offset for signal handling */
# define EXIT_SIGINT 130			/* Interrupt program, normally Ctrl+C */
# define EXIT_SIGQUIT 131			/* Interrupt program, normally Ctrl+\ */

/* Hashtable */
# define HASH_TABLE_SIZE 1031		/* Hashtable total size */
# define HASH_RIGHT_OFFSET 24		/* Right bit-shifting offset */
# define HASH_LEFT_OFFSET 4			/* Left bit-shifting offset */
# define HASH_LIMITER 0xf0000000	/* Hashing limiter */

/* Colors */
# define RESET		"\001\x1b[0m\002"	/* ANSI code for reseting colors */
# define RED		"\001\x1b[31m\002"	/* ANSI color code for red */
# define GREEN		"\001\x1b[32m\002"	/* ANSI color code for green */
# define MAGENTA	"\001\x1b[35m\002"	/* ANSI color code for magenta */
# define CYAN		"\001\x1b[36m\002"	/* ANSI color code for cyan */

# define PROMPT_MAX_LENGTH 4096	/* Max length allowed for custom prompt */

extern int					g_exit_value;	/* Global exit code variable */

typedef struct sigaction	t_sigaction;	/* Used for signal handling */
typedef struct stat			t_stat;			/* Used for file checking */
typedef struct dirent		t_dirent;		/* Used for wildcards */

/* Input type identifier */
typedef enum e_input
{
	IN_STDIN,
	IN_INFILE,
	IN_HEREDOC
}	t_input;

/* Output type identifier */
typedef enum e_output
{
	OUT_STDOUT,
	OUT_TRUNC,
	OUT_APPEND
}	t_output;

/* Used for identifying parsing tokens */
typedef enum e_token
{
	TOK_WORD,
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_REDIR_TRUNC,
	TOK_REDIR_APPEND,
	TOK_REDIR_INFILE,
	TOK_REDIR_HEREDOC,
	TOK_WILDCARD,
	TOK_OPEN_PARENTHESIS,
	TOK_CLOSE_PARENTHESIS
}	t_token;

/* Used for identifying command line connections */
typedef enum e_connector
{
	NONE,
	PIPE,
	AND,
	OR
}	t_connector;

/* Used to set I/O of every command */
typedef struct s_files
{
	t_output	which_output;
	t_input		which_input;
	char		*infile;
	char		*outfile;
}	t_files;

/* Basic structure of a hashtable node */
typedef struct s_hnode
{
	char				*key;
	char				*value;
	struct s_hnode		*next;
}	t_hnode;

/* Hashtable structure, used for storing environment variables */
typedef struct s_hash_table
{
	t_hnode	*item[HASH_TABLE_SIZE];
}	t_hash_table;

/* Doubly linked list node, used for tokenization */
typedef struct s_node
{
	char			*data;
	t_token			tok;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

/* Used to keep every command's I/O, status, depth and identifier (PID) */
typedef struct s_workspace
{
	int		**fd;
	int		*wstatus;
	int		*depth;
	pid_t	*pid;
}	t_workspace;

/* Used to store all commands with it's respective paths, arguments and I/O's */
typedef struct s_command_table
{
	int			cmds_amount;
	int			*depth;
	char		**cmd_path;
	char		***args;
	t_files		*files;
	t_connector	*connector;
}	t_command_table;

/* Main data structure, used to contain almost all structures defined */
typedef struct s_minishell
{
	t_command_table	cmd;
	t_hash_table	env;
	t_node			*input;
	int				fd_err;
	int				should_wait;
}	t_minishell;

#endif /* INTERNALS_H */
