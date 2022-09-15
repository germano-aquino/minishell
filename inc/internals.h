/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:54:38 by maolivei          #+#    #+#             */
/*   Updated: 2022/09/14 16:37:09 by maolivei         ###   ########.fr       */
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
# define REGULAR_TOKENS "<>|&"
# define PARSER_TOKENS "$'\""

# define ERR_QUOTES "there are unclosed quotes"
# define ERR_SYNTAX "syntax error near unexpected token "
# define TRUNC_STR "`>'"
# define APPEND_STR "`>>'"
# define INPUT_STR "`<'"
# define HEREDOC_STR "`<<'"
# define PIPE_STR "`|'"
# define OR_STR "`||'"
# define AND_STR "`&&'"
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

/* Colors */
# define RESET		"\001\x1b[0m\002"	/* ANSI code for reseting colors */
# define RED		"\001\x1b[31m\002"	/* ANSI color code for red */
# define GREEN		"\001\x1b[32m\002"	/* ANSI color code for green */
# define MAGENTA	"\001\x1b[35m\002"	/* ANSI color code for magenta */
# define CYAN		"\001\x1b[36m\002"	/* ANSI color code for cyan */

extern int					g_exit_value;	/* Global exit code variable */

typedef struct sigaction	t_sigaction;	/* Used for signal handling */
typedef struct stat			t_stat;			/* Used for ile checking */
typedef struct dirent		t_dirent;		/* Used for wildcards */

/* Input type identifier */
typedef enum e_input
{
	Stdin,
	Infile,
	Heredoc
}	t_input;

/* Output type identifier */
typedef enum e_output
{
	Stdout,
	Truncate,
	Append
}	t_output;

/* Used to set I/O of every command */
typedef struct s_files
{
	t_output	which_output;
	t_input		which_input;
	char		*infile;
	char		*outfile;
}	t_files;

/* Used for identifying parsing tokens */
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

typedef enum e_connector
{
	NONE,
	PIPE,
	AND,
	OR
}	t_connector;

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

/* Used to keep track of every command I/O, status and identifier (PID) */
typedef struct s_workspace
{
	int		**fd;
	int		*wstatus;
	pid_t	*pid;
}	t_workspace;

/* Used to store all commands with it's respective paths, arguments and I/O's */
typedef struct s_command_table
{
	int			cmds_amount;
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
