/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 14:40:00 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/05 14:40:42 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check(char *buff)
{
	//	printf("%d,%s\n", ft_strlen(buff), buff);
	if (ft_strlen(buff) == 4 && ft_strncmp(buff, "exit", 4) == 0)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (ft_strlen(buff) > 4 && ft_strncmp(buff, "exit ", 5) == 0)
	{
		write(1, "exit\n", 5);
		return (end(buff));
	}
	else
		return (1);
}
int		checkcote(char *buff)
{
	int	i;
	int	a;

	i = 0;
	while (buff[i] == ' ')
		i++;
	while (buff[i] != ' ')
		i++;
	while (buff[i] == ' ')
		i++;
	while(buff[i] != 34 && buff[i] != 39)
		i++;
	a = i + 1;
	while(buff[a] != 34 && buff[a] != 39)
		a++;
//	if

//	printf("[%c]\n", buff[i]);
	return (0);
}


