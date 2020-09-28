/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:51:47 by chgilber          #+#    #+#             */
/*   Updated: 2020/09/28 17:16:20 by chgilber         ###   ########.fr       */
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
	printf("joinjoin = -> [%s][%d]\n", all->dir[*inc], *inc);
	free(tmp);
}
