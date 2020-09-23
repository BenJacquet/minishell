/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:46:22 by chgilber          #+#    #+#             */
/*   Updated: 2020/09/21 17:49:11 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	silence(t_all all)
{
	int i;
	int len;

	i = 1;
	if (all.dir[1])
	{
		len = ft_strlen(all.dir[1]);
		i =  ((len == 3 && (ft_strncmp(all.dir[1], "-n ", 3) == 0)) ||
		 (len == 2 && (ft_strncmp(all.dir[1], "-n", 2) == 0)) ||
		 (len == 4 && (ft_strncmp(all.dir[1], "'-n'", 4) == 0)) ||
			(len == 4 && (ft_strncmp(all.dir[1], "\"-n\"", 4) == 0))) ? 0 : 1;
	}
	return (i);
}

int	join(t_all *all, char *buff, int inc, char quote)
{
	int	i;

	i = 0;
	
	while (buff[i] != quote)
		i++;
	all->dir[inc] = malloc(sizeof(char) * i + 2);
	all->dir[inc] = ft_strncpy(all->dir[inc], buff, i);
	if (inc == 0 && ft_strcmp(all->dir[inc], "-n") == 0)
	{
		all->stop = 0;
		return (i + 1);
	}
	write(1, all->dir[inc], ft_strlen(all->dir[inc]));
	return (i + 1);
}

int	printnoquote(t_all all)
{
	int	i;

	i = 1;
	if (all.dir[1])
		i = silence(all) == 0 ? 2 : 1;
	while (all.dir[i])
	{
		write(1, all.dir[i], ft_strlen(all.dir[i]));
		silence(all) == 1 ? write(1, " ", 1) : 0;
		i++;
	}
	return (silence(all));
}

int	printifquote(int i, t_all all)
{
	int	j;

	j = 0;
	
	while (all.buff[i])
	{
		if (all.buff[i] == ' ')
			while (all.buff[i + 1] == ' ')
				i++;
		if (all.buff[i] == '\'')
		{
			i = i + join(&all, all.buff + i + 1, j, '\'');
			j++;
		}
		else if (all.buff[i] == '\"')
		{
			i = i + join(&all, all.buff + i + 1, j, '\"');
			j++;
		}
		else
			write(1, &all.buff[i], 1);
		i++;
	}
	return (all.stop);
}

int	echo(t_all all)
{
	int	i;

	all.buff = all.pdir[all.data - all.countpipe];
	printf("[%s]\n" , all.buff);
	i = ft_strlen(all.dir[0]) + 1;
	all.stop = 1;
	if (all.dir[1])
	{
		if ((checksquote(all.buff + i) % 2 == 0 && checksquote(all.buff + i) >
					1) || (checkdquote(all.buff + i) % 2 == 0 &&
						checkdquote(all.buff + i) > 1))
		{
		//	freedir(all.dir);
			all.dir = newdir(all.dir, all.buff + i);
			all.stop = printifquote(i, all);
		}
		else
			all.stop = printnoquote(all);
	}
	else
		printnoquote(all);
	if (all.stop == 1)
		write(1, "\n", 1);
	return (0);
}
