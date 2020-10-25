/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:50:19 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/20 12:51:30 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		update_return(t_all *all, int new)
{
	if (all->ret)
	{
		if (all->ret->value)
			free(all->ret->value);
		all->ret->value = ft_itoa(new);
	}
	return (0);
}

char	**update_env(t_all *all, char **old)
{
	char	**env;

	if (all->env_replaced == 1)
		free_tab(old);
	env = ft_list_to_tab(all->env, 0, 0);
	all->env_replaced = 1;
	return (env);
}
