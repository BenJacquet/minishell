/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 12:35:39 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/08 18:57:41 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset_find_name(char *var, t_env *env, int op)
{
    int i;
    char *name;

    i = ft_varlen(var, 0);
    if (!(name = malloc(sizeof(char) * i + 1)))
        return (-1);
    ft_strlcpy(name, var, i);
    i += op;
    while (env)
    {
        if (ft_strcmp(name, env->name) == 0)
        {
            free(name);
            return (ft_export_edit(var + i, env, op));
        }
        if (!env->next)
            env->next = new_elem(var);
        env = env->next;
    }
    free(name);
    return (0);
}

int ft_unset_check_name(char *var)
{
    int i;

    i = 0;
    if (var[i] != '\0')
    {
        if (ft_isdigit(var[i]) || var[i] == '=')
            return (ft_put_error("not a valid identifier", var, 1));

            return (ft_put_error("not a valid identifier", var, 1));
    }
    return (0);
}

char **ft_unset(char *var, char **env)
{
    return (env);
}
