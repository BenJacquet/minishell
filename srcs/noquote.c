/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:32:05 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/09 14:35:24 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		noquoteinit(int *inc, char *buff, int *fusion)
{
	int	i;

	*fusion = (*inc > 0 && (buff[0] != ' ')
			&& (buff[1] != '<' && buff[1] != '>')) ? 1 : 0;
	i = (buff[1] == ' ') ? 2 : 1;
	while (buff[i] && buff[i] != '\'' && buff[i] != ' ' && buff[i] != '\"')
		i++;
	return (i);
}

int		noquote(t_all *all, char *buff, int *inc)
{
	int	i;
	int fusion;

	i = noquoteinit(inc, buff, &fusion);
	buff = tokla(all, buff, &i, (buff[1] == ' ') ? 2 : 1);
	if (all->diff == -666)
		return (0);
	if (ft_count_word(buff + (all->u + (buff[1] == ' ') ? 2 : 1), " ") > 0)
		i = noquoteinit(inc, buff, &fusion);
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
	return ((i));
}
