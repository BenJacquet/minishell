/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:05:48 by chgilber          #+#    #+#             */
/*   Updated: 2019/10/20 21:22:08 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*start;

	if (!lst || !(f) || !del)
		return (NULL);
	if (!(tmp = ft_lstnew(f(lst->content))))
		return (NULL);
	start = tmp;
	tmp = tmp->next;
	lst = lst->next;
	while (lst->next != NULL)
	{
		if (!(tmp = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		tmp = tmp->next;
		lst = lst->next;
	}
	return (start);
}
