/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 12:01:29 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/10 16:02:22 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeok(t_all all, char c, int i)
{
	all.pipe++;
	if (ft_strlen(all.buff) > i + 1)
	{
		if (all.buff[i + 1] == c || i == 0)
		{
			write(2, "minishell: ", 11);
			write(2, "syntax error near unexpected token '", 36);
			if (i != 0)
				write(2, &c, 1);
			write(2, &c, 1);
			write(2, "'\n", 2);
			return (-666);
		}
	}
	all.pipe = (ft_strlen(all.buff) == i + 1) ? all.pipe - 1 : all.pipe;
	return (all.pipe);
}

int	pipecount(t_all all, char *str, char c)
{
	int i;

	i = 0;
	all.pipe = 0;
	while (str[i])
	{
		if (str[i] == '\'' && checksquote(str) % 2 == 0)
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '\"' && checkquote(str) % 2 == 0)
		{
			i++;
			while (str[i] != '\"')
				i++;
		}
		if (str[i] == c)
			all.pipe = pipeok(all, c, i); //all.pipe++;
		i++;
	}
	return (all.pipe);
}
