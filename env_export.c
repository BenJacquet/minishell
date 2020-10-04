/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:01:17 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/23 14:37:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *ft_export_edit(t_env *var, t_env *env)
{
	t_env *head;

	head = env;
	if (var)
	{
		if (var->op == 1)
		{
			free(env->value);
			env->value = ft_strtrim(ft_strdup(var->value), "\'\"");
		}
		else if (var->op == 2)
			env->value = ft_strjoinf(env->value, ft_strtrim(var->value, "\'\""));
	}
	return (head);
}

t_env *ft_export_find_name(t_env *var, t_env *env)
{
	t_env *head;

	head = env;
	while (env)
	{
		if (ft_strcmp(var->name, env->name) == 0)
		{
			ft_export_edit(var, env);
			return (head);
		}
		if (!env->next)
			env->next = elem_dup(var);
		env = env->next;
	}
	return (head);
}

/*
** RETURN =-1 : ERREUR
** RETURN = 0 : NO OP
** RETURN = 1 : OP = "="
** RETURN = 2 : OP = "+="
*/

int ft_export_check_name(char *var)
{
	int i;

	i = 0;
	if (var)
	{
		if (var[i] != '\0')
		{
			if (ft_isdigit(var[i]) || var[i] == '=')
				return (ft_put_error("not a valid identifier\n", var, 1));
			while (ft_isalnum(var[i]) || var[i] == '_')
				i++;
			if (var[i] == '\0')
				return (0);
			else if (var[i] == '=')
				return (1);
			else if (ft_strncmp(&var[i], "+=", 2) == 0)
				return (2);
			return (ft_put_error("not a valid identifier\n", var, 1));
		}
	}
	return (1);
}

int ft_export_null(t_env *env)
{
	int i;
	int j;
	char **new;
	char *tmp;

	i = 0;
	j = 0;
	new = ft_list_to_tab(env, 1);
	while (new[i])
	{
		if (new[i + 1] && j == i)
			j++;
		if (ft_strcmp(new[i], new[j]) > 0)
		{
			tmp = new[i];
			new[i] = new[j];
			new[j] = tmp;
			i = -1;
			j = 0;
		}
		i++;
	}
	ft_puttab(new);
	free(new);
	return (0);
}

int ft_export_core(t_all *all)
{
	int i;
	t_env *var_lst;

	i = 1;
	if (all->dir[1] == NULL || all->dir[1][0] == '\0')
		return (ft_export_null(all->env));
	for (int j = 0; all->pdir[j]; j++)
		printf("all->pdir[%d]=%s\n", j, all->pdir[j]);
	var_lst = ft_tab_to_list(&all->dir[1]);
	while (all->dir[i])
	{
		if (ft_export_check_name(all->dir[i]) >= 0)
			all->env = ft_export_find_name(var_lst, all->env);
		i++;
		var_lst = var_lst->next;
	}
	//free de var_lst a ajouter;
	return (0);
}

/*int ft_export_core(t_all *all, char *var)
{
	int i;
	int ret;
	t_env *var_lst;

	all->buff = all->pdir[all->data - all->countpipe];
	i = ft_strlen(all->dir[0]) + 1;
	printf("old_all->buff + %d=%s\n", i, all->buff + i);
	all->stop = 1;
	if (all->dir[1] == NULL)
		return (ft_export_null(all->env));
	for (int j = 0; all->dir[j];j++)
		printf("old_all->dir[%d]=%s\n", j, all->dir[j]);
	if (all->dir[1])
	{
		if ((checksquote(all->buff + i) % 2 == 0 && checksquote(all->buff + i) >
					1) || (checkdquote(all->buff + i) % 2 == 0 &&
						checkdquote(all->buff + i) > 1))
		{
			freedir(all->dir);
			all->dir = newdir(all->dir, all->buff + i);
			join_if_quote(i, *all);
		}
	for (int j = 0; all->dir[j];j++)
		printf("new_all->dir[%d]=%s\n", j, all->dir[j]);
	}
	i = 0;
	while (all->dir[i])
	{
		free(all->ret->value);
		if ((ret = (ft_export_check_name(all->dir[i])) >= 0))
			all->env = ft_export_find_name(var_lst, all->env);
		all->ret->value = (ret == -1 ? ft_itoa(1) : ft_itoa(0));
		i++;
		var_lst = var_lst->next;
	}
	//free de var_lst a ajouter;
	return (0);
}*/