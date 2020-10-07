/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectioned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:38:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/07 18:39:54 by chgilber         ###   ########.fr       */
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
			all->shouldi[inc] = 1;
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
	all->shouldi = malloc(sizeof(int *) * len);
	while (i < len)
	{
		all->shouldi[i] = 0;
		i++;
	}
	return (0);
}
