/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectioned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:38:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/13 17:56:54 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		croco(t_all *all, char *buff, int len, int inc)
{
	int	i;

	i = 2;
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
	while (i < len)
	{
		all->shouldi[i] = 1;
		i++;
	}
	all->shouldi[i] = 0;
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
