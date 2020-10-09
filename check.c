/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:40:00 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/09 15:25:29 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		checkonlyret(char *buff, t_all *all)
{
	int i;

	i = all->i;
	i = 0;
	if (!buff)
		return (1);
	while (buff[i] == ' ')
		i++;
	if (ft_strlen(buff + i) == 4 && ft_strncmp(buff + i, "exit", 4) == 0)
		return (0);
	if (ft_strlen(buff + i) > 4 && ft_strncmp(buff + i, "exit ", 5) == 0)
		return (0);
	else
		return (1);
}

int		check(char *buff, t_all *all)
{
	int i;

	i = 0;
	if (!buff)
		return (1);
	while (buff[i] == ' ')
		i++;
	if (ft_strlen(buff + i) == 4 && ft_strncmp(buff + i, "exit", 4) == 0)
	{
		write(1, "exit\n", 5);
		free(all->ret->value);
		all->ret->value = ft_itoa(0);
		return (0);
	}
	if (ft_strlen(buff + i) > 4 && ft_strncmp(buff + i, "exit ", 5) == 0)
	{
		write(1, "exit\n", 5);
		return (end(buff, all));
	}
	else
		return (1);
}

int		checkquote(char *buff)
{
	int	i;
	int	a;
	int u;

	i = 0;
	a = 0;
	u = 0;
	while (buff[i])
	{
		while (buff[i] && (buff[i] != 34 && buff[i] != 39))
			i++;
		if (buff[i] && buff[i] == 34)
			a++;
		if (buff[i] && buff[i] == 39)
			u++;
		if (buff[i] && (buff[i] == 34 || buff[i] == 39))
			i++;
	}
	if (a % 2 != 0 || u % 2 != 0)
	{
		write(1, "No multilines\n", 14);
		return (1);
	}
	return (0);
}

int		checksquote(char *buff)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (buff[i])
	{
		while (buff[i] && (buff[i] != 39))
			i++;
		if (buff[i] && buff[i] == 39)
		{
			a++;
			i++;
		}
	}
	return (a);
}

int		checkdquote(char *buff)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (buff[i])
	{
		while (buff[i] && (buff[i] != 34))
			i++;
		if (buff[i] && buff[i] == 34)
		{
			a++;
			i++;
		}
	}
	return (a);
}
