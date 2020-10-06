/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelance.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:44:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/06 16:29:56 by chgilber         ###   ########.fr       */
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
				dir[i] = NULL;
				i++;
			}
			free(dir);
			dir = NULL;
		}
	}
	return (0);
}

int		freelance(t_all *all)
{
	int	i;

	i = 0;
	if (all->i == 0)
		write(1, "exit\n", 5);
	if (all->dir && (all->dir != NULL))
		freedir(all->dir);
	if (all->buff)
		free(all->buff);
	if (all->pdir)
		freedir(all->pdir);
	return (ft_atoi(all->ret->value));
}
