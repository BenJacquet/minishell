/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 12:01:29 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/13 16:35:37 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	message(t_all all, char c, int i)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token '", 36);
	if ((ft_strlen(all.buff) > i + 1 && all.buff[i + 1] == c ) || i == 0)
		write(2, &all.buff[i], 1);
	if ((ft_strlen(all.buff) > i + 1 && all.buff[i + 1] == c ))
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
		else
			write(1, "No multilines\n", 14);
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
			all.pipe = pipeok(all, c, i);
		i++;
	}
	return (all.pipe);
}
