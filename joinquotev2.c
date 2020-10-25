/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinquotev2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:21:09 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/25 16:10:54 by jabenjam         ###   ########.fr       */
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

	here = all->data - all->countpipe;
	i = 0;
	inc = 0;
	free_tab(all->dir);
	if ((checksquote(all->xdir[here]) % 2 == 0 &&
				checksquote(all->xdir[here]) > 1) ||
			(checkdquote(all->xdir[here]) % 2 == 0 &&
			checkdquote(all->xdir[here]) > 1))
	{
		initcroco(all, here);
		all->dir = newdirquote(all->dir, cnt(i, all, here));
		all->stop = ifquotev2(i, all, here, inc);
		i = 0;
	}
	else
	{
		all->dir = ft_split(all->xdir[all->data - all->countpipe], ' ');
		crocodir(all);
	}
	return (0);
}

int		multidir(t_all *all, char ***env)
{
	all->here = 0;
	while (all->here <= all->tube)
	{
		joinquotev2(all);
		for (int i = 0; all->dir[i]; i++)
			printf("all->dir[%d]=[%s]\n", i,all->dir[i]);
		if (all->here == 0)
			all->around = 1;
		else if (all->here == all->tube)
			all->around = 0;
		else
			all->around = 2;
		all->countpipe = checkquote(all->buff) ? 0 : all->countpipe;
		tokentranslate(all);
		pipeornotpipe(all, env);
		all->countpipe++;
		all->here++;
	}
	printf("countpipe=[%d]\n", all->countpipe);
	all->countpipe--;
	all->tube = 0;
	return (0);
}

