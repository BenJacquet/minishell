/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:01:17 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/15 14:30:37 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export_edit(char *var, t_env *env, int op)
{
    int len;
    char *new;

    if (var)
    {
        if (op == 1)
        {
            free(env->value);
            if (!(env->value = malloc(sizeof(char) * ft_strlen(var))))
                return (-1);
            env->value = ft_strdup(var);
        }
        else if (op == 2)
        {
            len = ft_strlen(var) + ft_strlen(env->value);
            new = ft_strjoin(env->value, var);
            free(env->value);
            env->value = new;
        }
    }
    return (0);
}

int ft_export_find_name(char *var, t_env *env, int op)
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
            else
                return (ft_put_error("not a valid identifier\n", var, 1));
        }
    }
    return (0);
}

int ft_export_null(char **env)
{
    int i;
    int j;
    char **new;
    char *tmp;

    i = 0;
    j = 0;
    new = tab_dup(env);
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
    ft_putenv(new);
    free(new);
    return (0);
}

char **ft_export_core(char *var, char **env)
{
    int i;
    int op;
    t_env *lst;
    char **vars;

    i = 0;
    if (var == NULL)
    {
        ft_export_null(env);
        return (env);
    }
    vars = ft_split(var, ' ');
    lst = ft_tab_to_list(env);
    while (vars[i])
    {
        if ((op = ft_export_check_name(vars[i])) >= 1)
            ft_export_find_name(vars[i], lst, op);
        i++;
    }
    free_tab(vars);
    return (ft_list_to_tab(lst));
    //AJOUTER FREE DE LA LISTE PRECEDENTE
}