/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:01:17 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/06 17:42:16 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_export_edit(t_env *var, t_env *env)
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

t_env	*ft_export_find_name(t_env *var, t_env *env)
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
    return (0);
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

int		ft_export_core(t_all *all, char *var)
{
    int i;
    char **vars;
	t_env *var_lst;

    i = 0;
    if (var == NULL)
        return (ft_export_null(all->env));
    var_lst = ft_tab_to_list(vars = ft_split(var, ' '));
    while (vars[i])
    {
        if (ft_export_check_name(vars[i]) >= 0)
		{
			expand_value(var_lst, all);
			all->env = ft_export_find_name(var_lst, all->env);
		}
		i++;
		var_lst = var_lst->next;
    }
	//free de var_lst a ajouter;
    free_tab(vars);
    return (0);
}