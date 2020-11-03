/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:07:55 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/28 19:13:07 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**newdirquote(char **dir, int count)
{
	dir = malloc(sizeof(char *) * (count + 1));
	dir[count] = NULL;
	return (dir);
}

char	*tokla(t_all *all, char *buff, int *end, int mode)
{
	int	i;

	i = 2;
	if (mode == 1)
		i = (buff[1] == ' ') ? 2 : 1;
	all->dolhere = 0;
	while (buff[i] && i < *end)
	{
		if (buff[i] == '$' && all->kotey != 3)
		{
			dolar(all, buff + i, i);
			buff = all->pdir[all->data - all->countsmc] + all->u - i + (mode == 0 ? 1 : 0);
			printf("tokla buff = [%s]\n", buff);
			printf("tokla pdir = [%s]\n",all->pdir[all->data - all->countsmc]);
			all->kotey = 0;
			if (mode == 1)
			*end = all->diff + ((buff[1] == ' ') ? 2 : 1);
			else
				*end = all->diff + 2;
			return (buff);
		}
		i++;
	}
	all->kotey = 0;
	return (buff);
}
int		noquote(t_all *all, char *buff, int *inc)
{
	int	i;
	int fusion;

	fusion = (*inc > 0 && (buff[0] == '\'' || buff[0] == '\"')
			&& (buff[1] != '<' && buff[1] != '>')) ? 1 : 0;
	i = (buff[1] == ' ') ? 2 : 1;
	while (buff[i] && buff[i] != '\'' && buff[i] != ' ' && buff[i] != '\"')
		i++;
	buff = tokla(all, buff, &i, (buff[1] == ' ') ? 0 : 1);
//	printf("i = %d\n", i);
	printf("noquote buff = [%s]\n", buff + ((buff[1] == ' ') ? 2 : 1));
	printf("noquote pdir = [%s]\n",all->pdir[all->data - all->countsmc]);
	if (fusion == 0 && ((buff[1] == ' ') ? i > 2 : i > 1))
	{
		all->dir[*inc] = malloc(sizeof(char) * i + 1);
		all->dir[*inc] = ft_strncpy(all->dir[*inc],
				buff + ((buff[1] == ' ') ? 2 : 1), i - 1);
		i = (buff[i] == ' ') ? i : i - 1;
		(*inc)++;
	}
	else if (fusion == 1)
	{
		joinjoin(all, buff - 1, inc, i + 1);
		i = (buff[i] == ' ') ? i : i - 1;
		(*inc)++;
	}
//	printf("allu = %d et i = %d et len = %d\n" , all->u, i, ft_strlen(all->pdir[all->data -all->countsmc]));
	return ((i < ft_strlen(all->pdir[all->data -all->countsmc])) ? i : ft_strlen(all->pdir[all->data -all->countsmc]));
}

int		ifjoin(t_all *all, char *buff, int *inc, char quote)
{
	int		i;

	i = 2;
	printf("ifjoin buff = [%s]\n", buff + 2);
	while (buff[i] != quote)
		i++;
	printf("ifjoin buff avant = [%s] et %d\n", buff  + 2, i );
	croco(all, buff, i, *inc);
	buff = tokla(all, buff, &i, 0);
	printf("ifjoin buff = [%s] et %d\n", buff  + 2, i );
	if (*inc > 0 && (buff[0] == ' ' || buff[0] == '<' || buff[0] == '>')
			&& buff[2] != quote)
	{
		all->dir[*inc] = malloc(sizeof(char) * i);
		all->dir[*inc] = ft_strncpy(all->dir[*inc], buff + 2, i - 2);
	}
	else if (*inc > 0 && i != 2)
		joinjoin(all, buff, inc, i);
	else
	{
		all->dir[*inc] = malloc(sizeof(char) * i);
		all->dir[*inc] = ft_strncpy(all->dir[*inc], buff + 2, i - 2);
	}
	printf("allu = %d et i = %d et len = %d\n" , all->u, i, ft_strlen(all->pdir[all->data -all->countsmc]));
	return (i);
}

int		ifquote(t_all *all, int here, int inc)
{
	while (all->u < ft_strlen(all->pdir[here]) && all->pdir[here][all->u])
	{
		while (all->pdir[here][all->u] == ' ')
			all->u++;
		if (all->pdir[here][all->u] == '\'')
		{
			all->u = all->u + ifjoin(all, all->pdir[here] + all->u - 1, &inc, '\'');
			inc++;
		}
		else if (all->pdir[here][all->u] == '\"')
		{
			all->u = all->u + ifjoin(all, all->pdir[here] + all->u - 1, &inc, '\"');
			inc++;
		}
		else if (all->pdir[here][all->u])
			all->u = all->u + noquote(all, all->pdir[here] + all->u - 1, &inc);
		else
			break ;
		printf("boucle pdir = [%s] et %d\n",all->pdir[all->data - all->countsmc], all->u);
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
	all->dolhere = 0;
	freedir(all->dir);
/*	if ((checksquote(all->pdir[here]) % 2 == 0 &&
				checksquote(all->pdir[here]) > 1) ||
			(checkdquote(all->pdir[here]) % 2 == 0 &&
			checkdquote(all->pdir[here]) > 1))
	{
*/		initcroco(all, here);
		all->dir = newdirquote(all->dir, cnt(0, all, here));
		all->stop = ifquote(all, here, inc);
/*	}
	else
	{
		all->dir = ft_split(all->pdir[all->data - all->countsmc], ' ');
		crocodir(all);
	}
*/	return (0);
}
