/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:31:51 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/28 01:28:29 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TOKENS "<>|&$\"\'*"
# define FORBIDDEN_CHARS "\\;"
# define WORD_CHARS "=-_+/()[]{}"

# define HASH_TABLE_SIZE 1031

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
}	t_node;

typedef struct s_command_table
{
	char	**cmd_path;
	char	***args;
}	t_command_table;


typedef struct s_minishell
{
	t_command_table	cmd;
	t_hash_table	env;
	int				fd[2];
	t_node			files[2];
	t_node			*input;
	int				pipes_amount;
}	t_minishell;

int		buff_to_input(t_minishell *data, const char *str, t_token tok);
void	tokenizer(t_minishell *data, char *buff);
void	display_input(t_node *input);
void	free_input(t_node **begin);

//Utils.c
size_t	max_size(char *s1, char *s2);
void	ft_free_2d_char_ptr(char ***ptr);
int		ft_chr_in_str(const char *str, char ch);

//hash_table_utils.c
int		hash_function(char	*key);
t_hnode	*create_item(char *key, char *value);
void	free_item(t_hnode *item);
void	ht_free(t_hash_table	*table);
void	display_htable(t_hash_table *table);

//hash_table.c
void	ht_insert(t_hash_table *table, char *key, char *value);
char	*ht_search(t_hash_table *table, char *key);
void	ht_delete(t_hash_table *table, char *key);

#endif