/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:55:45 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/12 15:53:36 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_cmd_table(t_command_table *cmd)
{
	int	cmd_pos;
	int	i;

	cmd_pos = -1;
	while (++cmd_pos < cmd->cmds_amount)
	{
		if (cmd->cmd_path[cmd_pos])
			printf("cmd_path: %s\n", cmd->cmd_path[cmd_pos]);
		else
			printf("cmd_path[%d]: not found\n", cmd_pos);
		i = -1;
		while (cmd->args[cmd_pos][++i])
			printf("args: %s\n\n", cmd->args[cmd_pos][i]);
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
		"Word", "File", "Dollar",
		"Pipe", "Double_Pipe",
		"Great", "Double_Great",
		"Less", "Double_Less",
		"Ampersand", "Double_Ampersand",
		"Quote", "Double_Quote",
		"Wildcard"
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
