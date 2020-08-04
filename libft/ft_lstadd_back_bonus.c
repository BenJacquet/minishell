/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 13:33:15 by chgilber          #+#    #+#             */
/*   Updated: 2019/10/16 20:42:01 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *now)
{
	t_list	*tmp;

	if (!alst || !now)
		return ;
	tmp = *alst;
	if (*alst == NULL)
		*alst = now;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = now;
	}
}
