/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:34:53 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/20 22:29:09 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void	ft_bzero(void *block, size_t size);

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_isascii(int c);

int		ft_isdigit(int c);

int		ft_isprint(int c);

char	*ft_itoa(int n);

void	*ft_memchr(const void *block, int c, size_t size);

int		ft_memcmp(const void *s1, const void *s2, size_t size);

void	*ft_memmove(void *to, const void *from, size_t size);

void	*ft_memset(void *block, int c, size_t size);

void	*ft_memcpy(void *to, const void *from, size_t size);

void	*ft_memccpy(void *to, const void *from, int c, size_t size);

void	ft_putchar_fd(char c, int fd);

void	ft_putstr_fd(char *s, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

char	*ft_strchr(const char *str, int c);

char	*ft_strrchr(const char *str, int c);

char	*ft_strdup(const char *str);

char	*ft_strjoin(const char *s1, const char *s2);

int		ft_strncmp(const char *s1, const char *s2, size_t size);

char	*ft_strnstr(const char *big, const char *little, size_t size);

char	*ft_strtrim(char const *str, char const *set);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

char	*ft_substr(char const *s, unsigned int start, size_t len);

size_t	ft_strlcat(char *dst, const char *src, size_t size);

size_t	ft_strlcpy(char *dest, const char *src, size_t size);

size_t	ft_strlen(const char *str);

int		ft_tolower(int c);

int		ft_toupper(int c);

int		ft_atoi(const char *str);

void	*ft_calloc(size_t count, size_t eltsize);

char	**ft_split(char const *s, char c);

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new_lst);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new_lst);

void	ft_lstdelone(t_list *lst, void (*del)(void *));

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *));

char	*get_next_line(int fd, int free_buff);

#endif