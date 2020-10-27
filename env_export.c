/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:01:17 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/27 16:38:53 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_edit(t_env *var, t_env *env)
{
	if (var)
	{
		if (var->op == 1)
		{
			free(env->value);
			env->value = ft_strtrim(ft_strdup(var->value), "\'\"");
		}
		else if (var->op == 2)
			env->value = ft_strjoinf(env->value,
						ft_strtrim(var->value, "\'\""));
		env->op = 1;
	}
}

t_env	*ft_export_find_name(t_env *var, t_env *env, int new)
{
	t_env	*head;

	head = env;
	while (env)
	{
		if (ft_strcmp(var->name, env->name) == 0)
		{
			ft_export_edit(var, env);
			return (head);
		}
		if (!env->next && new == 1)
		{
			env->next = elem_dup(var);
			return (head);
		}
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

int		ft_export_check_name(char *var)
{
	int		i;

	i = 0;
	if (var)
	{
		if (var[i] != '\0')
		{
			if (ft_isdigit(var[i]) || var[i] == '=')
				return (ft_put_error("not a valid identifier", var, 1));
			while (ft_isalnum(var[i]) || var[i] == '_')
				i++;
			if (var[i] == '\0')
				return (0);
			else if (var[i] == '=')
				return (1);
			else if (ft_strncmp(&var[i], "+=", 2) == 0)
				return (2);
			return (ft_put_error("not a valid identifier", var, 1));
		}
	}
	return (1);
}

int		ft_export_null(t_env *env)
{
	int		i;
	int		j;
	char	**new;
	char	*tmp;

	i = 0;
	j = 0;
	new = ft_list_to_tab(env, 1, 0);
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
	return (0);
}

int		ft_export_core(t_all *all)
{
	int		i;
	t_env	*var_lst;
	t_env	*head;

	i = 1;
	if (all->dir[1] == NULL || all->dir[1][0] == '\0')
		return (ft_export_null(all->env));
	var_lst = ft_tab_to_list(&all->dir[1], 0);
	head = var_lst;
	while (all->dir[i])
	{
		if (ft_export_check_name(all->dir[i]) >= 0)
			all->env = ft_export_find_name(var_lst, all->env, 1);
		else
			update_return(all, 1);
		i++;
		var_lst = var_lst->next;
	}
	free_vars(head);
	return (0);
}
