/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:51:47 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/12 18:12:31 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	joinjoin(t_all *all, char *buff, int *inc, int i)
{
	char	*tmp;

	(*inc)--;
	tmp = ft_strdup(all->dir[*inc]);
	free(all->dir[*inc]);
	all->dir[*inc] = malloc(sizeof(char) * i + ft_strlen(tmp) + 1);
	all->dir[*inc] = ft_strncpy(all->dir[*inc], tmp, ft_strlen(tmp));
	all->dir[*inc] = ft_strncat(all->dir[*inc], buff + 2, i - 2);
//	printf("joinjoin = -> [%s][%d]\n", all->dir[*inc], *inc);
	free(tmp);
}

int		crontold(t_all *all)
{
	char	*tmp[2];

	while (all->buff && ft_strlen(all->buff) > 0 && all->i == 0)
	{
		tmp[0] = ft_strdup(all->buff);
		free(all->buff);
		all->i = get_next_line(0, &all->buff);
		tmp[1] = ft_strdup(all->buff);
		free(all->buff);
		all->buff = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
	}
	return (1);
}
