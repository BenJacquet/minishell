/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:16:26 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/04 17:51:44 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_dir()
{
	char *path;
	int len;
	int i;
	int a;

	path = NULL;
	path = getcwd(path, 0);
	i = 0;
	a = 0;
	while (path[i])
	{
		if (path[i] == '/')
			a = i;
		i++;
	}
	if (path[a])
	{
		len = strlen(path + a);
		write(1, path + a, len);
		write(1, " : ", 3);
		free(path);
	}
	return (0);
}
