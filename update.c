/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:50:19 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/26 19:57:21 by jabenjam         ###   ########.fr       */
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

int		update_pwd(t_all *all, int old)
{
	t_env	*pwd;
	char	*path;

	path = NULL;
	if (old == 1)
	{
		path = ft_getenv(all, "PWD", 0);
		pwd = new_elem(ft_strjoin("OLDPWD=", path));
	}
	else
	{
		path = getcwd(path, 0);
		pwd = new_elem(ft_strjoin("PWD=", path));
	}
	ft_export_find_name(pwd, all->env);
	free(path);
	free_var(pwd);
	return (0);
}
