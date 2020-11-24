/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectioned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:38:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/11/24 19:17:00 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		itscroco(char comp)
{
	if (comp == '>' || comp == '<')
		return (1);
	return (0);
}

int		croco(t_all *all, char *buff, int len, int inc)
{
	int	i;

	i = 2;
	all->kotey = (buff[1] && buff[1] == '\'') ? 3 : 2;
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
	all->kotey = 0;
	free(all->shouldi);
	all->shouldi = malloc(sizeof(int *) * (len + 1));
	while (i < len)
	{
		all->shouldi[i] = 1;
		i++;
	}
	all->shouldi[i] = 0;
	return (0);
}
