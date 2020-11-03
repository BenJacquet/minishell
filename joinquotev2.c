/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinquotev2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:21:09 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/26 18:45:02 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ifquotev2(int i, t_all *all, int here, int inc)
{
	while (all->xdir[here][i])
	{
		while (all->xdir[here][i] == ' ')
			i++;
		if (all->xdir[here][i] == '\'')
		{
			i = i + ifjoin(all, all->xdir[here] + i - 1, &inc, '\'');
			inc++;
		}
		else if (all->xdir[here][i] == '\"')
		{
			i = i + ifjoin(all, all->xdir[here] + i - 1, &inc, '\"');
			inc++;
		}
		else if (all->xdir[here][i])
			i = i + noquote(all, all->xdir[here] + i - 1, &inc);
		else
			break ;
	}
	all->dir[inc] = NULL;
	return (all->stop);
}

int		joinquotev2(t_all *all)
{
	int	i;
	int	inc;

	i = 0;
	inc = 0;
	free_tab(all->dir);
	initcroco(all, all->here);
	all->dir = newdirquote(all->dir, cnt(i, all, all->here));
	all->stop = ifquotev2(i, all, all->here, inc);
	i = 0;
	return (0);
}
