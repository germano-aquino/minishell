/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenato- <grenato-@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 11:32:14 by grenato-          #+#    #+#             */
/*   Updated: 2022/04/16 17:22:49 by grenato-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*new_lst;
	t_list	*iter;

	if (!lst)
		return (0);
	new_lst = NULL;
	while (lst)
	{
		iter = ft_lstnew(f(lst->content));
		if (!iter)
			ft_lstclear(&iter, del);
		else
			ft_lstadd_back(&new_lst, iter);
		lst = lst->next;
	}
	return (new_lst);
}
