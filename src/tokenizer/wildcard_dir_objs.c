/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_dir_objs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: germano <germano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:39:13 by germano           #+#    #+#             */
/*   Updated: 2022/08/16 16:39:47 by germano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#inlcude <minishell.h>

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
