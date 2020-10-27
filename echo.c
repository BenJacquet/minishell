/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:46:22 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/27 19:16:20 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	silence(char *buff)
{
	int i;
	int u;
	int len;

	i = 1;
	if (buff)
	{
		len = ft_strlen(buff);
		i = ((len == 3 && (ft_strncmp(buff, "-n ", 3) == 0)) ||
				(len == 2 && (ft_strncmp(buff, "-n", 2) == 0)) ||
				(len == 4 && (ft_strncmp(buff, "'-n'", 4) == 0)) ||
				(len == 4 && (ft_strncmp(buff, "\"-n\"", 4) == 0))) ? 0 : 1;
		if (len > 2 && ft_strncmp(buff, "-n", 2) == 0)
		{
			u = 2;
			while (buff[u] && buff[u] == 'n')
				u++;
			i = (u == len) ? 0 : 1;
		}
	}
	return (i);
}

int	printnoquote(t_all all)
{
	int	i;

	i = 1;
	while (all.dir[i])
	{
		i = silence(all.dir[i]) == 0 ? i + 1 : i;
		if (silence(all.dir[i]) != 0)
			break ;
	}
	while (all.dir[i])
	{
		write(1, all.dir[i], ft_strlen(all.dir[i]));
		(i != ft_tablen(all.dir) - 1) ? write(1, " ", 1) : 0;
		i++;
	}
	return (silence(all.dir[1]));
}

int	echo(t_all all)
{
	all.stop = 1;
	all.stop = printnoquote(all);
	if (all.stop == 1)
		write(1, "\n", 1);
	return (0);
}
