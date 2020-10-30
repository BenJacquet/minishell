/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:50:19 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/28 16:32:42 by jabenjam         ###   ########.fr       */
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

/*
void	update_wd(t_all *all, char *path) //POUR NE PAS SORTIR DU DIR APRES AVOIR RM
{
	if (all->wd_backup)
		free(all->wd_backup);
	all->wd_backup = ft_strdup(path);
}*/

int		update_pwd(t_all *all, int old, int new)
{
	t_env	*pwd;
	char	*path;

	path = NULL;
	if (old == 1)
	{
		path = ft_getenv(all, "PWD", 0);
		pwd = (path[0] == '\0' ? new_elem("OLDPWD", 0) :
				new_elem(ft_strjoin("OLDPWD=", path), 1));
	}
	else
	{
		path = getcwd(path, 0);
		pwd = new_elem(ft_strjoin("PWD=", path), 1);
	}
	ft_export_find_name(pwd, all->env, new);
	free(path);
	free_var(pwd);
	return (0);
}

void		new_env(t_all *all)
{
	t_env	*var;

	all->env = new_elem("_=/usr/bin/env", 0);
	var = new_elem("SHLVL=1", 0);
	ft_export_find_name(var, all->env, 1);
	free_var(var);
	var = new_elem("OLDPWD", 0);
	ft_export_find_name(var, all->env, 1);
	free_var(var);
	update_pwd(all, 0, 1);
}

void		update_shlvl(t_all *all)
{
	char	*value;
	t_env	*var;
	int		i;

	value = ft_getenv(all, "SHLVL", 0);
	i = ft_atoi(value);
	free(value);
	value = ft_itoa(i + 1);
	var = new_elem(ft_strjoin("SHLVL=", value), 1);
	ft_export_find_name(var, all->env, 1);
	free(value);
	free_var(var);
}