/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinquotebis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 11:52:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/28 19:39:13 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (inc);
}
