/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:31:45 by grenato-          #+#    #+#             */
/*   Updated: 2022/06/08 00:45:34 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free_buff(char **ptr, t_buffer *buff)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	if (buff != NULL && buff->begin != NULL)
	{
		free(buff->begin);
		buff->begin = NULL;
		buff->end = NULL;
	}
}

int	ft_read_from_fd(t_buffer *buff_add, int fd)
{
	int	sz;

	sz = read(fd, (*buff_add).begin, BUFFER_SIZE);
	if (!sz || sz == -1)
		return (0);
	(*buff_add).begin[sz] = '\0';
	(*buff_add).end = (*buff_add).begin;
	return (1);
}

char	*ft_line_alloc(char **ptr, int *size, int first_allocation)
{
	char	*new;
	int		index;

	*size += BUFFER_SIZE;
	new = (char *) malloc(sizeof(char) * *size);
	if (!new)
		return (NULL);
	index = 0;
	new[index] = '\0';
	if (!first_allocation)
	{
		while (index < *size - BUFFER_SIZE - 1)
		{
			new[index] = *(*ptr + index);
			index++;
		}
		free(*ptr);
		*ptr = NULL;
	}
	return (new);
}

char	*ft_get_line(t_buffer *buff_add, int fd)
{
	char	*line;
	int		line_size;
	int		index;
	int		line_not_end;

	line_size = 1;
	line = ft_line_alloc(&line, &line_size, 1);
	index = 0;
	line_not_end = 1;
	while (line_not_end)
	{
		if (*buff_add->end == '\0' && !ft_read_from_fd(buff_add, fd))
			return (line);
		line[index] = *buff_add->end;
		if (*buff_add->end == '\n')
			line_not_end = 0;
		(*buff_add).end++;
		index++;
		if (index % BUFFER_SIZE == 0)
			line = ft_line_alloc(&line, &line_size, 0);
		line[index] = '\0';
	}
	return (line);
}

char	*get_next_line(int fd, int free_buff)
{
	static t_buffer	buff;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 256)
		return (NULL);
	if (buff.begin == NULL)
	{
		buff.begin = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		buff.end = buff.begin;
		if (!buff.begin || !ft_read_from_fd(&buff, fd))
		{
			free(buff.begin);
			buff.begin = NULL;
			buff.end = NULL;
			return (NULL);
		}
	}
	if (!free_buff)
		line = ft_get_line(&buff, fd);
	else
		line = NULL;
	if (free_buff || line[0] == '\0')
		ft_free_buff(&line, &buff);
	return (line);
}
