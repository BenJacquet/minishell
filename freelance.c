/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelance.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:44:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/06 18:48:01 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
