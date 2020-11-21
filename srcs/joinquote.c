/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:31:32 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/21 13:49:48 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**newdirquote(char **dir, int count)
{
	dir = malloc(sizeof(char *) * (count + 2));
	dir[count] = NULL;
	return (dir);
}

int		ifquote(t_all *all, int here, int inc)
{
	while (all->u < ft_strlen(all->pdir[here]) && all->pdir[here][all->u])
	{
		while (all->pdir[here][all->u] == ' ')
			all->u++;
		if (all->pdir[here][all->u] == '\'')
		{
			all->u = all->u +
				ifjoin(all, all->pdir[here] + all->u - 1, &inc, '\'');
			inc++;
		}
		else if (all->pdir[here][all->u] == '\"')
		{
			all->u = all->u +
				ifjoin(all, all->pdir[here] + all->u - 1, &inc, '\"');
			inc++;
		}
		else if (all->pdir[here][all->u])
			all->u = all->u + noquote(all, all->pdir[here] + all->u - 1, &inc);
		else
			break ;
	}
	all->dir[inc] = NULL;
	return (all->stop);
}

int		joinquote(t_all *all)
{
	int	inc;
	int	here;

	here = all->data - all->countsmc;
	all->u = 0;
	inc = 0;
	free_tab(all->dir);
	initcroco(all, here);
	all->dir = newdirquote(all->dir, cnt(0, all, here));
	all->stop = ifquote(all, here, inc);
	return (0);
}
