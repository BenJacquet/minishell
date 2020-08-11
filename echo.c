/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:46:22 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/09 19:12:14 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lenquote(char *buff, char quote)
{
	int	i;

	i = 1;
	while(buff[i] != quote)
		i++;
	return (i);
}

int	join(char **dir, char *buff, int inc, char quote)
{
	int	i;

	i = 0;
	while (buff[i] != quote)
			i++;
	dir[inc] = malloc(sizeof(char) * i + 2);
	dir[inc] = ft_strncpy(dir[inc], buff, i);
	//	write(1, dir[inc], 5);
	return (i + 1);
}

int	echo(char *buff, char **dir)
{
	int	i;
	int	j;
	int	stop;

	i = ft_strlen(dir[0]);
	j = 1;
	if ((checksquote(buff + i) % 2 == 0 && checksquote(buff + i) > 1) ||
			(checkdquote(buff + i) % 2 == 0 && checkdquote(buff + i) > 1))
	{
		freedir(dir);
		dir = newdir(&*dir, buff + i);
	//	i = 0;
		while (buff[i])
		{
			while (buff[i] == ' ')
				i++;
			if (buff[i] == '\'')
			{
				i = i + join(&*dir, buff + i + 1, j, '\'');
				write(1, dir[j], ft_strlen(dir[j]));
				write(1, " ", 1);
				j++;
			}
			else if (buff[i] == '\"')
			{
				i = i + join(&*dir, buff + i + 1, j, '\"');
				write(1, dir[j], ft_strlen(dir[j]));
				write(1, " ", 1);
				j++;
			}
			else
				write(1, &buff[i], 1);
					i++;
		}
	}
	//stop = j;
//	j = 1;
	else //(i == ft_strlen(buff) || checkquote(buff) == 0)
	{
		j = 1;
		i = 7;
		while (dir[j])
		{
			write(1, dir[j], ft_strlen(dir[j]));
			write(1, " ", 1);
			i = i + ft_strlen(dir[j]);
	//		free(dir[j]);
			j++;
		}
		//	write(1, "\n", 1);
	}
/*	j = 0;
	if (dir[j])
	{
		while (dir[j])
		{
			write(1, dir[j], ft_strlen(dir[j]));
			write(1, " ", 1);
			j++;
		}
	}
*/	write(1, "\n", 1);
	return (0);
}
