/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 12:01:29 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/16 18:53:52 by chgilber         ###   ########.fr       */
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

int	pipecount(t_all all, char c)
{
	int i;

	i = 0;
	all.pipe = 0;
	while (all.buff[i])
	{
		if (all.buff[i] == '\'' && checksquote(all.buff) % 2 == 0)
		{
			i++;
			while (all.buff[i] != '\'')
				i++;
		}
		if (all.buff[i] == '\"' && checkquote(all.buff) % 2 == 0)
		{
			i++;
			while (all.buff[i] != '\"')
				i++;
		}
		if (all.buff[i] == c)
			all.pipe++;
		i++;
	}
//	pipeok(all);// pas fonctionelle need return
	return (all.pipe);
}
