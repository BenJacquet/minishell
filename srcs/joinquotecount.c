/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinquotecount.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:21:20 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/05 22:21:44 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		hmwtoken(t_all *all, int here)
{
	int	i;
	int	dol;

	i = 0;
	dol = 0;
	while (all->pdir[here][i])
	{
		if (all->pdir[here][i] == '$' || itscroco(all->pdir[here][i]) == 1)
			dol++;
		i++;
	}
	return ((dol * 10));
}

int		noquotecount(char *buff, int *inc)
{
	int	i;

	i = 0;
	if (buff[i])
	{
		i = buff[0] == ' ' ? 1 : 0;
		while (buff[i] && buff[i] != '\'' && buff[i] != ' ' && buff[i] != '\"')
			i++;
		if ((buff[0] == ' ') ? i > 1 : i > 0)
		{
			i = (buff[i] == ' ') ? i : i - 1;
			(*inc)++;
		}
	}
	return (i);
}

int		ifjoincount(char *buff, char quote)
{
	int	i;

	i = 0;
	while (buff[i] != quote)
		i++;
	return (i + 1);
}

int		cnt(int i, t_all *all, int here)
{
	int	inc;

	inc = 0;
	while (all->pdir[here][i])
	{
		while (all->pdir[here][i] == ' ')
			i++;
		if (all->pdir[here][i] == '\'')
		{
			i = i + ifjoincount(all->pdir[here] + i + 1, '\'') + 1;
			inc++;
		}
		else if (all->pdir[here][i] == '\"')
		{
			i = i + ifjoincount(all->pdir[here] + i + 1, '\"') + 1;
			inc++;
		}
		else if (all->pdir[here][i])
			i = i + noquotecount(all->pdir[here] + i, &inc) + 1;
		else
			break ;
	}
	return ((inc + hmwtoken(all, here)));
}
