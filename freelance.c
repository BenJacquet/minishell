/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelance.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:44:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/19 16:15:20 by jabenjam         ###   ########.fr       */
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

int		freelance(t_all *all, char **env)
{
	int ret;

	ret = 0;
	if (all->ret)
	{
		ret = ft_atoi(all->ret->value);
		free_vars(all->ret);
	}
	if (all->i == 0)
		write(1, "exit\n", 5);
	if (all->dir)
		free_tab(all->dir);
	if (all->buff)
		free(all->buff);
	if (all->pdir)
		free_tab(all->pdir);
	if (all->env)
		free_vars(all->env);
	if (all->env_replaced)
		free_tab(env);
	if (all->xdir)
		free_tab(all->xdir);
	return (ret);
}
