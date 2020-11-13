/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifjoin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:31:09 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/09 14:31:10 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		ifjoininit(char *buff, int quote)
{
	int	i;

	i = 2;
//	printf("ifjoin buff avant = [%s] et %d\n", buff  + 2, i );
	while (buff[i] && buff[i] != quote)
		i++;
	return (i);
}

int		ifjoin(t_all *all, char *buff, int *inc, char quote)
{
	int		i;

	i = ifjoininit(buff, quote);
	croco(all, buff, i, *inc);
	buff = tokla(all, buff, &i, 2);
//		printf("ifjoin\n");
	if (*inc > 0 && (buff[0] == ' ' || buff[0] == '<' || buff[0] == '>')
			&& buff[2] != quote)
	{
		all->dir[*inc] = malloc(sizeof(char) * i);
		all->dir[*inc] = ft_strncpy(all->dir[*inc], buff + 2, i - 2);
	}
	else if (*inc > 0 && buff[0] != ' ')
		joinjoin(all, buff, inc, i);
	else
	{
		all->dir[*inc] = malloc(sizeof(char) * i);
		all->dir[*inc] = ft_strncpy(all->dir[*inc], buff + 2, i - 2);
	}
	return (i);
}
