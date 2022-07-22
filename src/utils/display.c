/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:55:45 by grenato-          #+#    #+#             */
/*   Updated: 2022/07/20 20:51:17 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	display_cmd_table(t_command_table *cmd)
{
	int	cmd_pos;
	int	i;

	cmd_pos = -1;
	while (++cmd_pos < cmd->cmds_amount)
	{
		if (cmd->cmd_path[cmd_pos] != NULL)
			ft_printf("cmd_path: %s\n", cmd->cmd_path[cmd_pos]);
		else
			ft_printf("cmd_path[%d]: not found\n", cmd_pos);
		i = -1;
		while (cmd->args[cmd_pos][++i] != NULL)
			ft_printf("args: %s\n\n", cmd->args[cmd_pos][i]);
	}
}

// void	display_htable(t_hash_table *table)
// {
// 	int		i;
// 	int		count;
// 	int		total;
// 	t_hnode	*item;

// 	i = -1;
// 	total = 0;
// 	while (++i < HASH_TABLE_SIZE)
// 	{
// 		item = table->item[i];
// 		if (item != NULL)
// 		{
// 			count = 0;
// 			total++;
// 			ft_printf("key: %s\nvalue: %s\nindex:%d\tcount: %d\n\n", \
// 				item->key, item->value, i, count);
// 			while (item->next != NULL)
// 			{
// 				total++;
// 				item = item->next;
// 				count++;
// 				ft_printf("key: %s\nvalue: %s\nindex:%d\tcount: %d\n\n", \
// 					item->key, item->value, i, count);
// 			}
// 		}
// 	}
// 	ft_printf("total: %d\n", total);
// }

void	display_htable(t_hash_table *table)
{
	int		i;
	t_hnode	*item;

	i = -1;
	while (++i < HASH_TABLE_SIZE)
	{
		item = table->item[i];
		if (item != NULL)
		{
			ft_printf("%s=%s\n", item->key, item->value);
			while (item->next != NULL)
			{
				item = item->next;
				ft_printf("%s=%s\n", item->key, item->value);
			}
		}
	}
}

void	display_input(t_node *input)
{
	int	i;
	char const*	tokens[] = {"Word", "File", "Dollar", "Pipe", "Double_Pipe", "Great", "Double_Great", "Less", "Double_Less", "Ampersand", "Double_Ampersand", "Quote", "Double_Quote", "Wildcard"};

	i = -1;
	if (input == NULL)
		ft_printf("Input is empty.\n");
	else
	{
		while (input != NULL)
		{
			ft_printf("i: %d\n", ++i);
			ft_printf("token: %s\ndata: %s\n\n", tokens[input->tok], input->data);
			input = input->next;
		}
	}
}
