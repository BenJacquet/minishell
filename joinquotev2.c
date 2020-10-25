/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinquotev2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:21:09 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/25 18:16:40 by chgilber         ###   ########.fr       */
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
	int	here;

	i = 0;
	inc = 0;
	free_tab(all->dir);
	if ((checksquote(all->xdir[all->here]) % 2 == 0 &&
				checksquote(all->xdir[all->here]) > 1) ||
			(checkdquote(all->xdir[all->here]) % 2 == 0 &&
			checkdquote(all->xdir[all->here]) > 1))
	{
		initcroco(all, all->here);
		all->dir = newdirquote(all->dir, cnt(i, all, all->here));
		all->stop = ifquotev2(i, all, all->here, inc);
		i = 0;
	}
	else
	{
		all->dir = ft_split(all->xdir[all->here], ' ');
		crocodir(all);
	}
	return (0);
}

int		multidir(t_all *all, char ***env, int fd[all->tube][2])
{
	all->here = 0;
	while (all->here <= all->tube)
	{
		joinquotev2(all);
		if (all->here == 0)
			all->around = 1;
		else if (all->here == all->tube)
			all->around = 0;
		else
			all->around = 2;
		all->countsmc = checkquote(all->buff) ? 0 : all->countsmc;
		tokentranslate(all);
		action(all, env, fd);
		all->here++;
	}
	all->countsmc--;
	all->tube = 0;
	return (0);
}
