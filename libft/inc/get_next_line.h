/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:31:53 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/20 22:25:49 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_buffer{
	char	*begin;
	char	*end;
}				t_buffer;

int		ft_read_from_fd(t_buffer *buff_add, int fd);

char	*ft_line_alloc(char **ptr, int *size, int first_allocation);

char	*ft_get_line(t_buffer *buff_add, int fd);

char	*get_next_line(int fd, int free_buff);

#endif