/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: germano <germano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:11:23 by grenato-          #+#    #+#             */
/*   Updated: 2022/08/16 15:54:51 by germano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	amount_objs_in_current_dir(t_bool begin_with_dot)
{
	t_dirent	*files;
	DIR			*dir;
	int			str_amount;

	dir = opendir(".");
	files = readdir(dir);
	str_amount = 0;
	while (files != NULL)
	{
		if (begin_with_dot || *files->d_name != '.')
			str_amount++;
		files = readdir(dir);
	}
	closedir(dir);
	return (str_amount);
}

char	**get_objects_in_current_directory(char *exp)
{
	t_dirent	*files;
	DIR			*dir;
	int			str_amount;
	char		**str;
	t_bool		begin_with_dot;

	begin_with_dot = FALSE;
	if (*exp == '.')
		begin_with_dot = TRUE;
	str_amount = amount_objs_in_current_dir(begin_with_dot);
	str = ft_calloc(str_amount + 1, sizeof(char *));
	dir = opendir(".");
	files = readdir(dir);
	str_amount = 0;
	while (files != NULL)
	{
		if (begin_with_dot || *files->d_name != '.')
			str[str_amount++] = ft_strdup(files->d_name);
		files = readdir(dir);
	}
	closedir(dir);
	return (str);
}

t_bool	filter_is_obj_suffix(char *obj, char *filter)
{
	int	obj_len;
	int	filter_len;

	obj_len = ft_strlen(obj);
	filter_len = ft_strlen(filter);
	while (filter_len >= 0)
	{
		if (filter[filter_len] != obj[obj_len])
			return (FALSE);
		filter_len--;
		obj_len--;
	}
	return (TRUE);
}

t_bool	is_a_valid_obj(char **filters, char *obj, char *exp)
{
	t_bool	has_prefix;
	t_bool	has_suffix;
	char	*temp;
	int		i;

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
	if (temp == NULL || (has_suffix && !filter_is_obj_suffix(obj, filters[i - 1])))
		return (FALSE);
	return (TRUE);
}

t_node	*delete_wildcard_token(t_node *input, t_node **last)
{
	t_node	*ret;

	ret = input->prev;
	(*last)->next = input->next;
	input->next->prev = *last;
	input->prev = NULL;
	input->next = NULL;
	free_input(&input);
	return (ret);
}

t_node	*wildcard_handler(t_node *input, char *exp)
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
		input = delete_wildcard_token(input, &prev);
	else
		input->tok = Word;
	ft_free_matrix((void *) &objs);
	ft_free_matrix((void *) &filters);
	return (input);
}

void	wildcard_expansion(t_minishell *data)
{
	t_node	*input;

	input = data->input;
	while (input != NULL)
	{
		if (input->tok == Wildcard)
			input = wildcard_handler(input, input->data);
		else
			input = input->next;
	}
}
