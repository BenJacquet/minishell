/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:07:55 by chgilber          #+#    #+#             */
/*   Updated: 2020/09/20 16:18:57 by chgilber         ###   ########.fr       */
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

	i = 0;
//	printf("noquote - > [%s]\n", buff);
	if (buff[i])
	{
		i = buff[0] == ' ' ? 1 : 0;
		while (buff[i] && buff[i] != '\'' && buff[i] != ' ' && buff[i] != '\"')
			i++;
		if ((buff[0] == ' ') ? i > 1 : i > 0)
		{
			all->dir[*inc] = malloc(sizeof(char) * i + 1);
			all->dir[*inc] = ft_strncpy(all->dir[*inc],
					buff + ((buff[0] == ' ') ? 1 : 0), i);
			i = (buff[i] == ' ') ? i : i - 1;
			(*inc)++;
		}
	}
	return (i);
}

int		ifjoin(t_all *all, char *buff, int *inc, char quote)
{
	int		i;
	char	*tmp;

	i = 0;
	while (buff[i] != quote)
		i++;
	all->dir[*inc] = malloc(sizeof(char) * i + ((*inc > 0) ? ft_strlen(all->dir[*inc - 1]) + 1  : 2));
	if (*inc > 1 && all->dir[*inc - 1][ft_strlen(all->dir[*inc - 1]) - 1] == ' ')
		all->dir[*inc] = ft_strncpy(all->dir[*inc], buff, i);
	else if (*inc > 1)
	{
		(*inc)--;
		tmp = ft_strdup(all->dir[*inc]);
//		printf("buff = -> [%s], i{%d}\n", buff, i);
		free(all->dir[*inc]);
		free(all->dir[*inc + 1]);
	all->dir[*inc] = malloc(sizeof(char) * i + ft_strlen(tmp) + 1);
		all->dir[*inc] = ft_strncpy(all->dir[*inc], tmp, ft_strlen(tmp));
		all->dir[*inc] = ft_strncat(all->dir[*inc], buff, i);
//		printf("dir[inc] = -> [%s],\n", all->dir[*inc]);
		free(tmp);
	}
	else
		all->dir[*inc] = ft_strncpy(all->dir[*inc], buff, i);
	return (i + 1);
}

int		ifquote(int i, t_all *all, int here)
{
	int	inc;

	inc = 0;
	while (all->pdir[here][i])
	{
		while (all->pdir[here][i] == ' ')
			i++;
		if (all->pdir[here][i] == '\'')
		{
			i = i + ifjoin(all, all->pdir[here] + i + 1, &inc, '\'') + 1;
			inc++;
		}
		else if (all->pdir[here][i] == '\"')
		{
			i = i + ifjoin(all, all->pdir[here] + i + 1, &inc, '\"') + 1;
			inc++;
		}
		else if (all->pdir[here][i])
			i = i + noquote(all, all->pdir[here] + i, &inc) + 1;
		else
			break ;
	}
	return (all->stop);
}

int		joinquote(t_all *all)
{
	int	i;
	int	here;

	here = all->data - all->countpipe;
	i = 0;
	freedir(all->dir);
	if ((checksquote(all->pdir[here] + i) % 2 == 0 &&
				checksquote(all->pdir[here] + i) > 1) ||
			(checkdquote(all->pdir[here] + i) % 2 == 0 &&
			checkdquote(all->pdir[here] + i) > 1))
	{
		all->dir = newdirquote(all->dir, cnt(i, all, here));
		all->stop = ifquote(i, all, here);
	}
	else
		all->dir = ft_split(all->pdir[all->data - all->countpipe], ' ');
	return (0);
}
