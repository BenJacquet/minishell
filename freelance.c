/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelance.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:44:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/09/21 19:03:15 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		freedir(char **dir)
{
	int	i;

	i = 0;
	if (dir && dir != NULL)
	{
		if (dir[0])
		{
			while (dir[i])
			{
				free(dir[i]);
				i++;
			}
			free(dir);
		}
	}
	return (0);
}

int		freelance(t_all *all)
{
	int	i;

	i = 0;
	if (all->dir && (all->dir != NULL))
		freedir(all->dir);
	if (all->buff)
		free(all->buff);
	if (all->pdir)
		freedir(all->pdir);
	return (ft_atoi(all->ret->value));
}
