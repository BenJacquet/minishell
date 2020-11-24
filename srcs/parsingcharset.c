/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingcharset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:49:55 by chgilber          #+#    #+#             */
/*   Updated: 2020/11/24 22:02:05 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		bouclebis(char *buff, int i, char quote)
{
	i++;
	while (buff[i] && buff[i] != quote)
		i++;
	if (buff[i] != quote)
		return (-666);
	else if (buff[i] == quote)
		i++;
	return (i);
}

int		whilewell(char *buff, int i)
{
	if (buff[i] && buff[i] == 34)
	{
		if (bouclebis(buff, i, 34) < i)
			return (0);
		else
			i = bouclebis(buff, i, 34);
	}
	else if (buff[i] && buff[i] == 39)
	{
		if (bouclebis(buff, i, 39) < i)
			return (0);
		else
			i = bouclebis(buff, i, 39);
	}
	else
		i = (buff[i]) ? i + 1 : i;
	return (i);
}

int		checkpars(t_all *all, char *buff)
{
	int i;

	i = all->i;
	i = 0;
	if (buff[0] == ';')
		return (pipecount(*all, buff, ';'));
	if (buff[0] == '|')
		return (pipecount(*all, buff, '|'));
	while (buff[i])
	{
		if (timide(buff + i))
			return (1);
		if (whilewell(buff, i))
			i = whilewell(buff, i);
		else
		{
			write(2, "No multilines\n", 14);
			return (1);
		}
		if (timide(buff + i) || (buff[i] == '|' && pipecount(*all, buff, '|')
			< 0) || (buff[i] == ';' && pipecount(*all, buff, ';') < 0))
			return (1);
	}
	return (0);
}
