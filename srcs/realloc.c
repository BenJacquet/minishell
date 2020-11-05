/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 13:17:31 by chgilber          #+#    #+#             */
/*   Updated: 2020/09/18 16:11:59 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*ft_realloc(char *buff, int len)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * len + 1);
	tmp = ft_strcpy(tmp, buff);
	free(buff);
	return (tmp);
}

char	**newdir(char **dir, char *buff)
{
	int		len;

	if (checksquote(buff) % 2 == 0 && checksquote(buff) > 1)
		len = checksquote(buff);
	if (checkdquote(buff) % 2 == 0 && checkdquote(buff) > 1)
		len = len + checkdquote(buff);
	dir = malloc(sizeof(char *) * (len + 2));
	dir[len + 1] = NULL;
	return (dir);
}
