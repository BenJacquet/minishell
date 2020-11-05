/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:58:16 by chgilber          #+#    #+#             */
/*   Updated: 2019/10/20 16:40:33 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	int		a;
	int		i;
	t_list	*tmp;
	t_list	*tomp;

	if (!lst)
		return ;
	if (!*lst || !del)
		return ;
	tomp = *lst;
	i = ft_lstsize(tomp);
	while (0 < i--)
	{
		tomp = *lst;
		a = 0;
		while (tomp && a < i)
		{
			tmp = tomp;
			tomp = tmp->next;
			a++;
		}
		del(tomp->content);
		free(tomp);
	}
	*lst = NULL;
}
