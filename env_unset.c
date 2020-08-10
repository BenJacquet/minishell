/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 12:35:39 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/10 16:58:16 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset_find_name(char *var, t_env *env)
{
    int i;
    t_env *bridge;

    while (env)
    {
        if (env->next)
            bridge = env->next;
        if (ft_strcmp(var, env->name) == 0)
        {
            free(env->name);
            free(env->value);
            free(env);
        }
        env = env->next;
    }
    return (0);
}

int ft_unset_check_name(char *var)
{
    int i;

    i = 0;
    if (var[i] != '\0')
    {
        if (ft_isdigit(var[i]) || var[i] == '=' || !ft_isalnum(var[i]) && var[i] != '_')
            return (ft_put_error("not a valid identifier", var, 1));
        while (ft_isalnum(var[i]) || var[i] == '_')
            i++;
        if (var[i] != '\0')
            return (ft_put_error("not a valid identifier", var, 1));
    }
    return (0);
}

char **ft_unset_core(char *var, char **env)
{
    t_env *lst;

    if (!var)
        return (env);
    if (!(ft_unset_check_name(var)))
        return (env);
    lst = ft_tab_to_list(env);
    ft_unset_find_name(var, lst);
    env = ft_list_to_tab(lst);
    return (env);
}
