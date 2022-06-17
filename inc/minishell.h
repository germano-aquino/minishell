/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: germano <germano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:31:51 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/17 17:48:52 by germano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TOKENS "<>|&$*"
# define QUOTES "\'\""
# define FORBIDDEN_CHARS "\\;"

typedef enum e_token
{
	Word,
	File,
	Dolar,
	Pipe,
	Double_Pipe,
	Great,
	Double_Great,
	Less,
	Double_Less,
	Ampersand,
	Double_Ampersand,
	Great_Ampersand,
	Less_Ampersand,
	Double_Great_Ampersand,
	Quote,
	Double_Quote,
	Wildcard
}	t_token;

typedef struct s_trienode
{
	char	*data;
	struct	s_trienode *next[256];
}	t_trienode;

typedef struct s_trie
{
	t_trienode	*root;
}	t_trie;

typedef struct s_node
{
	char			*data;
	t_token			tok;
	struct s_node	*next;
}	t_node;

typedef struct s_command_table
{
	char	**args;
}	t_command_table;


typedef struct s_minishell
{
	t_command_table	cmd;
	int				fd[3];
	t_node			files[3];
	t_node			*input;
	t_trie			env;
}	t_minishell;

int		ft_is_chr_in_str(const char *str, char ch);
int		buff_to_input(t_minishell *data, const char *str, t_token tok);
void	tokenizer(t_minishell *data, char *buff);
void	display_input(t_node *input);
void	free_input(t_node **begin);
void	populate_env(t_minishell *data, char *envp[]);
void	ft_free_2d_char_ptr(char ***ptr);
char	*get_trie_value(t_trienode *node, char *key);
#endif