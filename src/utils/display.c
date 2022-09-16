/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:55:45 by grenato-          #+#    #+#             */
/*   Updated: 2022/09/16 13:49:41 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_cmd_table(t_command_table *cmd)
{
	int	index;
	int	i;

	index = -1;
	while (++index < cmd->cmds_amount)
	{
		if (cmd->cmd_path[index])
			printf("cmd_path: %s\n", cmd->cmd_path[index]);
		else
			printf("cmd_path[%d]: not found\n", index);
		i = -1;
		while (cmd->args[index][++i])
			printf("args: %s\n\n", cmd->args[index][i]);
	}
}

void	display_htable(t_hash_table *table)
{
	int		i;
	int		count;
	int		total;
	t_hnode	*item;

	i = -1;
	total = 0;
	while (++i < HASH_TABLE_SIZE)
	{
		item = table->item[i];
		if (item)
		{
			count = 0;
			total++;
			printf("key: %s\nvalue: %s\nindex:%d\tcount: %d\n\n",
				item->key, item->value, i, count);
			while (item->next)
			{
				total++;
				item = item->next;
				count++;
				printf("key: %s\nvalue: %s\nindex:%d\tcount: %d\n\n",
					item->key, item->value, i, count);
			}
		}
	}
	printf("total: %d\n", total);
}

void	display_input(t_node *input)
{
	int			i;
	const char	*tokens[] = {
		"TOK_WORD",
		"TOK_PIPE", "TOK_OR",
		"TOK_REDIR_TRUNC", "TOK_REDIR_APPEND",
		"TOK_REDIR_INFILE", "TOK_REDIR_HEREDOC",
		"TOK_AND",
		"TOK_WILDCARD"
	};

	if (input == NULL)
		printf("Input is empty.\n");
	else
	{
		i = -1;
		while (input)
		{
			printf("i: %d\n", ++i);
			printf("token: %s\ndata: %s\n\n", tokens[input->tok], input->data);
			input = input->next;
		}
	}
}
