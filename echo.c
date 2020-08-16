/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:46:22 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/16 19:09:51 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join(char **dir, char *buff, int inc, char quote)
{
	int	i;

	i = 0;
	while (buff[i] != quote)
		i++;
	dir[inc] = malloc(sizeof(char) * i + 2);
	dir[inc] = ft_strncpy(dir[inc], buff, i);
	write(1, dir[inc], ft_strlen(dir[inc]));
	if (buff[i + 1] != ' ')
		write(1, " ", 1);
	return (i + 1);
}

int	printnoquote(char **dir)
{
	int	i;

	i = 1;
	if (dir[1])
		i = (ft_strcmp(dir[1], "-n") == 0) ? 2 : 1;
	while (dir[i])
	{
		write(1, dir[i], ft_strlen(dir[i]));
		write(1, " ", 1);
		i++;
	}
	return (i);
}

int	printifquote(char *buff, char **dir, int i)
{
	int	j;

	j = 0;
	while (buff[i])
	{
		if (buff[i] == ' ')
			while (buff[i + 1] == ' ')
				i++;
		if (buff[i] == '\'')
		{
			i = i + join(&*dir, buff + i + 1, j, '\'');
			j++;
		}
		else if (buff[i] == '\"')
		{
			i = i + join(&*dir, buff + i + 1, j, '\"');
			j++;
		}
		else
			write(1, &buff[i], 1);
		i++;
	}
	return (i);
}

int	echo(char *buff, char **dir)
{
	int	i;
	int	stop;

	i = ft_strlen(dir[0]) + 1;
	stop = 1;
	if (dir[1])
		stop = (ft_strcmp(dir[1], "-n") == 0) ? 0 : 1;
	if (dir[1])
	{
		if ((checksquote(buff + i) % 2 == 0 && checksquote(buff + i) > 1) ||
				(checkdquote(buff + i) % 2 == 0 && checkdquote(buff + i) > 1))
		{
			freedir(&*dir);
			dir = newdir(&*dir, buff + i);
			printifquote(buff, &*dir, i);
		}
	}
	else
		printnoquote(dir);
	if (stop == 1)
		write(1, "\n", 1);
	return (0);
}
