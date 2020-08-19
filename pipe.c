/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 12:01:29 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/17 14:44:21 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeok(t_all all)
{
	int i;

	i = 0;
	while (all.buff[i] == ' ')
		i++;
	if (all.buff[i] == '|')
	{
		write(1, "minishell: ", 11);
		write(1, "syntax error near unexpected token `|'\n", 39);
		return (0);
	}
	return (1);
}

int	pipecount(t_all all,char *str, char c)
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
			all.pipe++;
		i++;
	}
//	pipeok(all);// pas fonctionelle need return
	return (all.pipe);
}
