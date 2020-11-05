/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelance.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:44:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/28 18:56:31 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	freelancebis(t_all *all)
{
	if (all->dir)
		free_tab(all->dir);
	if (all->buff)
		free(all->buff);
	if (all->pdir)
		free_tab(all->pdir);
}

int		freelance(t_all *all)
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
	freelancebis(all);
	if (all->env)
		free_vars(all->env);
	if (all->xdir)
		free_tab(all->xdir);
	if (all->wd_backup)
		free(all->wd_backup);
	all->bad = free_red(all->bad);
	free(all->shouldi);
	return (ret);
}
