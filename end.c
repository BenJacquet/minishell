/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:30:12 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/05 12:13:32 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		end(char *buff)
{
	int		i;
	char	**arg;

	i = 0;
	arg = ft_split(buff, ' ');
	if (arg[1])
	{
		while (arg[1][i] && ft_isdigit(arg[1][i]) == 0)
			i++;
		if (i == ft_strlen(arg[1]))
		{
			write(1, "bash: exit: ls: numeric argument required\n", 42);
			return (255);
		}
		else
			return (atoi(arg[1]));
	}
	return (0);
}
