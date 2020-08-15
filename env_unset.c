/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 12:35:39 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/15 12:39:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset_find_name(char *var, t_env *current)
{
    t_env *backup;

    backup = NULL;
    if (ft_strcmp(var, current->name) == 0)
    {
        if (current->next)
            backup = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = backup->next;
        return (1);
    }
    while (current)
    {
        backup = current;
        if (ft_strcmp(var, current->name) == 0)
        {
            if (current->next)
                backup = current->next;
            free(current->name);
            free(current->value);
            free(current);
        }
        current = current->next;
    }
    return (0);
}

int ft_unset_check_name(char *var)
{
    int i;

    i = 0;
    if (var[i] != '\0')
    {
        if (ft_isdigit(var[i]) || var[i] == '=' || (!ft_isalnum(var[i]) && var[i] != '_'))
            return (ft_put_error("not a valid identifier\n", var, 1));
        while (ft_isalnum(var[i]) || var[i] == '_')
            i++;
        if (var[i] != '\0')
            return (ft_put_error("not a valid identifier\n", var, 1));
    }
    return (0);
}

char **ft_unset_core(char *var, char **env)
{
    t_env *lst;
    char **vars;
    int i;

    i = 0;
    if (!var)
        return (env);
    vars = ft_split(var, ' ');
    lst = ft_tab_to_list(env);
    while (vars[i])
    {
        if (ft_unset_check_name(vars[i]) >= 1)
            ft_unset_find_name(vars[i], lst);
        i++;
    }
    free_tab(vars);
    return (ft_list_to_tab(lst));
}
