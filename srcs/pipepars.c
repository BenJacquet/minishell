/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipepars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:20:44 by chgilber          #+#    #+#             */
/*   Updated: 2020/11/23 20:54:38 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	timide(char *buff)
{
	int i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '>')
		{
			if (buff[i + 1] && buff[i + 1] == '<')
			{
				write(2, "minishell: syntax error near unexpected token '<'\n"
						, 51);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	message(t_all all, char c, int i)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token '", 36);
	if ((ft_strlen(all.buff) > i + 1 && all.buff[i + 1] == c) || i == 0)
		write(2, &all.buff[i], 1);
	if ((ft_strlen(all.buff) > i + 1 && all.buff[i + 1] == c))
		write(2, &all.buff[i + 1], 1);
	write(2, "'\n", 2);
	return (-666);
}

int	pipeok(t_all all, char c, int i)
{
	all.pipe++;
	if (ft_strlen(all.buff) > i + 1)
		if (all.buff[i + 1] == '|' || all.buff[i + 1] == ';')
			return (message(all, c, i));
	if (i == 0)
		return (message(all, c, i));
	if (i + 1 == ft_strlen(all.buff) && i != 0 && c == '|')
	{
		if (all.buff[i - 1] == c && all.buff[i] == c)
			return (-666);
		return (-666);
	}
	all.pipe = (ft_strlen(all.buff) == i + 1) ? all.pipe - 1 : all.pipe;
	return (all.pipe);
}

int	pipecount(t_all all, char *str, char c)
{
	int i;

	i = 0;
	all.pipe = 0;
	all.buff = str;
	while (str[i])
	{
		if (str[i] == c)
			all.pipe = pipeok(all, c, i);
		if (all.pipe < 0)
			return (-666);
		i = quote(str, i);
	}
	return (all.pipe);
}
