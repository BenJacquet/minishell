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

int		cntv2(int i, t_all *all, int here)
{
	int	inc;

	inc = 0;
	while (all->xdir[here][i])
	{
		while (all->xdir[here][i] == ' ')
			i++;
		if (all->xdir[here][i] == '\'')
		{
			i = i + ifjoincount(all->xdir[here] + i + 1, '\'') + 1;
			inc++;
		}
		else if (all->xdir[here][i] == '\"')
		{
			i = i + ifjoincount(all->xdir[here] + i + 1, '\"') + 1;
			inc++;
		}
		else if (all->xdir[here][i])
			i = i + noquotecount(all->xdir[here] + i, &inc) + 1;
		else
			break ;
	}
	return (inc);
}

int		initcrocov2(t_all *all)
{
	int len;
	int i;

	i = 0;
	len = cntv2(i, all, all->here);
	all->kotey = 0;
	free(all->shouldi);
	all->shouldi = malloc(sizeof(int *) * (len + 1));
	while (i < len)
	{
		all->shouldi[i] = 1;
		i++;
	}
	all->shouldi[i] = 0;
	return (0);
}

int		joinquotev2(t_all *all)
{
	int	i;
	int	inc;

	i = 0;
	inc = 0;
	free_tab(all->dir);
	initcrocov2(all);
	all->dir = newdirquote(all->dir, cntv2(i, all, all->here));
	all->stop = ifquotev2(i, all, all->here, inc);
	i = 0;
	return (0);
}
