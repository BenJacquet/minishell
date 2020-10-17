/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:07:55 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/17 19:24:38 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**newdirquote(char **dir, int count)
{
	dir = malloc(sizeof(char *) * (count + 1));
	dir[count] = NULL;
	return (dir);
}

int		noquote(t_all *all, char *buff, int *inc)
{
	int	i;
	int fusion;

	//	printf("noquote - > [%s]\n", buff + 1);
	fusion = (*inc > 0 && (buff[0] == '\'' || buff[0] == '\"') && ( buff[1] != '<' && buff[1] != '>')) ? 1 : 0;
	i = (buff[1] == ' ') ? 2 : 1;
	while (buff[i] && buff[i] != '\'' && buff[i] != ' ' && buff[i] != '\"')
		i++;
	if (fusion == 0 && ((buff[1] == ' ') ? i > 2 : i > 1))
	{
		all->dir[*inc] = malloc(sizeof(char) * i + 1);
		all->dir[*inc] = ft_strncpy(all->dir[*inc],
				buff + ((buff[1] == ' ') ? 2 : 1), i - 1);
		i = (buff[i] == ' ') ? i : i - 1;
		//	printf("dirnoauote = -> [%s][%d]\n", all->dir[*inc], *inc);
		(*inc)++;
	}
	else if (fusion == 1)
	{
		joinjoin(all, buff - 1, inc, i + 1);
		i = (buff[i] == ' ') ? i : i - 1;
		(*inc)++;
	}
	return (i);
}

int		ifjoin(t_all *all, char *buff, int *inc, char quote)
{
	int		i;

	i = 2;
	while (buff[i] != quote)
		i++;
	croco(all, buff, i, *inc);
	//	printf("buffjoin = -> [%s], i{%d}\n", buff + 1, i);
	if (*inc > 0 && (buff[0] == ' ' || buff[0] == '<' || buff[0] == '>') && buff[2] != quote)
	{
		all->dir[*inc] = malloc(sizeof(char) * i);
		all->dir[*inc] = ft_strncpy(all->dir[*inc], buff + 2, i - 2);
	}
	else if (*inc > 0)
		joinjoin(all, buff, inc, i);
	else
	{
		all->dir[*inc] = malloc(sizeof(char) * i);
		all->dir[*inc] = ft_strncpy(all->dir[*inc], buff + 2, i - 2);
	}
	//	printf("dirquote = -> [%s][%d]\n", all->dir[*inc], *inc);
	return (i);
}

int		ifquote(int i, t_all *all, int here, int inc)
{
	while (all->pdir[here][i])
	{
		while (all->pdir[here][i] == ' ')
			i++;
		if (all->pdir[here][i] == '\'')
		{
			i = i + ifjoin(all, all->pdir[here] + i - 1, &inc, '\'');
			inc++;
		}
		else if (all->pdir[here][i] == '\"')
		{
			i = i + ifjoin(all, all->pdir[here] + i - 1, &inc, '\"');
			inc++;
		}
		else if (all->pdir[here][i])
			i = i + noquote(all, all->pdir[here] + i - 1, &inc);
		else
			break ;
	}
	all->dir[inc] = NULL;
	return (all->stop);
}

int		joinquote(t_all *all)
{
	int	i;
	int	inc;
	int	here;

	here = all->data - all->countpipe;
	i = 0;
	inc = 0;
	freedir(all->dir);
	if ((checksquote(all->pdir[here]) % 2 == 0 &&
				checksquote(all->pdir[here]) > 1) ||
			(checkdquote(all->pdir[here]) % 2 == 0 &&
			checkdquote(all->pdir[here]) > 1))
	{
		initcroco(all, here);
		all->dir = newdirquote(all->dir, cnt(i, all, here));
		all->stop = ifquote(i, all, here, inc);
		i = 0;
	}
	else
	{
		all->dir = ft_split(all->pdir[all->data - all->countpipe], ' ');
		crocodir(all);
	}
	return (0);
}

