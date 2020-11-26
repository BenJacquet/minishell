/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:40:00 by chgilber          #+#    #+#             */
/*   Updated: 2020/11/26 13:51:09 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
