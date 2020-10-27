/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:50:19 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/27 20:05:58 by jabenjam         ###   ########.fr       */
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

int		update_pwd(t_all *all, int old, int new)
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
		ft_export_find_name(pwd, all->env, new);
	free(path);
	free_var(pwd);
	return (0);
}

void		new_env(t_all *all)
{
	t_env	*var;

	var = new_elem("_=/usr/bin/env");
	all->env = new_elem("SHLVL=1");
	ft_export_find_name(var, all->env, 1);
	free_var(var);
	var = new_elem("OLDPWD");
	ft_export_find_name(var, all->env, 1);
	free_var(var);
	update_pwd(all, 0, 1);
}

void		update_shlvl(t_all *all)
{
	char	*name;
	char	*value;
	int		len;

	len = ft_strlen(all->exec) - 1;
	name = NULL;
	value = ft_getenv(all, "SHLVL", 0);
	while (len > 0 && all->exec[len] != '/')
	{
		len--;
		name = &all->exec[len + 1];
	}
/*	if (ft_strcmp(name, "bash") == 0 || ft_strcmp(name, "minishell") == 0 ||
		ft_strcmp(name, "sh") == 0 || ft_strcmp(name, "zsh") == 0)
	{
		if (value[0])
			
		else
			
	}*/
	free(value);
}