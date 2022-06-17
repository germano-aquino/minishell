/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trie.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: germano <germano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:57:23 by germano           #+#    #+#             */
/*   Updated: 2022/06/17 17:54:47 by germano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_trienode	*create_trie_node()
{
	t_trienode *new_node;
	int			i;

	new_node = (t_trienode *)malloc(sizeof(t_trienode));
	new_node->data = NULL;
	i = -1;
	while (++i < 256)
		new_node->next[i] = NULL;
	return (new_node);
}

char	*get_trie_value(t_trienode *node, char *key)
{
	unsigned int	index;
	char			*value;

	if (*key == '\0')
		value = ft_strdup(node->data);
	else
	{
		index = (unsigned int)*key;
		key++;
		value = get_trie_value(node->next[index], key);
	}
	return (value);
}

void	add_trie_node(t_trienode **node, char *key, char *value)
{
	unsigned int	index;

	if (*node == NULL)
		*node = create_trie_node();
	if (*key == '\0')
		(*node)->data = ft_strdup(value);
	else
	{
		index = (unsigned int)*key;
		key++;
		add_trie_node(&(*node)->next[index], key, value);
	}
}

void	populate_env(t_minishell *data, char *envp[])
{
	int		i;
	char	**key_value;

	i = -1;
	while (envp[++i] != NULL)
	{
		key_value = ft_split(envp[i], '=');
		add_trie_node(&data->env.root, key_value[0], key_value[1]);
		ft_free_2d_char_ptr(&key_value);
	}
}