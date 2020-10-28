/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectioned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:38:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/28 19:57:00 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		messagecroco(char **pdir, char c, int i, int j)
{
	if (pdir[i][j] == '>' || pdir[i][j] == '<')
	{
		write(2, "minishell: syntax error near unexpected token '", 48);
		if (pdir[i + 1])
		{
			write(2, &c, 1);
			write(2, "'\n", 2);
		}
		else
			write(2, "newline'\n", 10);
		return (1);
	}
	return (0);
}

void	crocofail(t_all *all, char **pdir, char c)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (pdir[0])
	{
		while (pdir[i])
		{
			j = ft_strlen(pdir[i]) - 1;
			while (pdir[i][j] == ' ')
				j--;
			if (messagecroco(pdir, c, i, j) == 1)
			{
				all->countsmc = 0;
				break ;
			}
			i++;
		}
	}
}

int		croco(t_all *all, char *buff, int len, int inc)
{
	int	i;

	i = 2;
	all->kotey[inc] = 2;
	while (buff[i] && i < len)
	{
		if (buff[i] == '<' || buff[i] == '>')
		{
			all->shouldi[inc] = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int		initcroco(t_all *all, int here)
{
	int len;
	int i;

	i = 0;
	len = cnt(i, all, here);
	all->shouldi = malloc(sizeof(int *) * (len + 1));
	all->kotey = malloc(sizeof(int *) * (len + 1));
	while (i < len)
	{
		all->shouldi[i] = 1;
		all->kotey[i] = 1;
		i++;
	}
	all->shouldi[i] = 0;
	all->kotey[i] = 0;
	return (0);
}

int		crocodir(t_all *all)
{
	int len;
	int i;

	i = 0;
	len = ft_tablen(all->dir);
	all->shouldi = malloc(sizeof(int *) * (len + 1));
	while (i < len)
		all->shouldi[i++] = 1;
	all->shouldi[i] = 0;
	return (0);
}
