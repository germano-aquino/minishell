/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maolivei <maolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:11:23 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/29 15:40:53 by maolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_bool	is_a_valid_obj(char **filters, char *obj, char *exp)
{
	t_bool	has_prefix;
	t_bool	has_suffix;
	char	*temp;
	int		i;

	if (!filters)
		return (TRUE);
	has_prefix = FALSE;
	has_suffix = FALSE;
	if (*exp != '*')
		has_prefix = TRUE;
	if (exp[ft_strlen(exp) - 1] != '*')
		has_suffix = TRUE;
	i = 0;
	if (has_prefix && ft_strncmp(filters[0], obj, ft_strlen(filters[0])) != 0)
		return (FALSE);
	temp = ft_strnstr(obj, filters[0], ft_strlen(obj));
	while (filters[++i] != NULL && temp != NULL)
		temp = ft_strnstr(temp, filters[i], ft_strlen(temp));
	if (temp == NULL
		|| (has_suffix && !filter_is_obj_suffix(obj, filters[i - 1])))
		return (FALSE);
	return (TRUE);
}

static t_node	*delete_wildcard_token(
	t_minishell *data, t_node *input, t_node **last)
{
	t_node	*ret;

	ret = input->prev;
	(*last)->next = input->next;
	if (input->next)
		input->next->prev = *last;
	input->prev = NULL;
	input->next = NULL;
	free_input(&input);
	if (ret == NULL)
	{
		ret = *last;
		while (ret->prev != NULL)
			ret = ret->prev;
		data->input = ret;
	}
	return (ret);
}

static t_node	*wildcard_handler(t_minishell *data, t_node *input, char *exp)
{
	char	**filters;
	char	**objs;
	int		i;
	t_node	*prev;

	prev = input->prev;
	objs = get_objects_in_current_directory(exp);
	filters = ft_split(exp, '*');
	i = -1;
	while (objs[++i] != NULL)
	{
		if (is_a_valid_obj(filters, objs[i], exp))
			prev = create_input(objs[i], Word, NULL, prev);
	}
	if (prev != input->prev)
		input = delete_wildcard_token(data, input, &prev);
	else
		input->tok = Word;
	ft_free_matrix((void *)&objs);
	ft_free_matrix((void *)&filters);
	return (input);
}

void	wildcard_expansion(t_minishell *data)
{
	t_node	*input;

	input = data->input;
	while (input != NULL)
	{
		if (input->tok == Wildcard)
			input = wildcard_handler(data, input, input->data);
		else
			input = input->next;
	}
}
