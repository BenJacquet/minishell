/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelance.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:44:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/09 18:44:11 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		freedir(char **dir)
{
	int	i;

	i = 0;
	if (dir)
	{
		while (dir[i])
		{
			free(dir[i]);
			i++;
		}
		free(dir);
	}
	return (0);
}

int		freelance(char **dir, char *buff)
{
	int	i;

	i = 0;
	if (dir)
	{
		while (dir[i])
		{
			free(dir[i]);
			i++;
		}
		free(dir);
	}
	free(buff);
	return (0);
}
