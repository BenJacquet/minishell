/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 12:35:39 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/08 14:22:51 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export_edit(char *var, t_env *env, int op)
{
    int len;
    char *new;

    printf("var=%s\n", var);
    if (var)
    {
        if (op == 1)
        {
            free(env->value);
            if (!(env->value = malloc(sizeof(char) * ft_strlen(var))))
                return (-1);
            env->value = ft_strdup(var);
            printf("env->value=%s\n", env->value);
        }
        else if (op == 2)
        {
            len = ft_strlen(var) + ft_strlen(env->value);
            new = ft_strjoin(env->name, var);
            free(env->value);
            env->value = new;
            printf("env->value=%s\n", env->value);
        }
    }
    return (0);
}

/*int ft_export_new(char *var, t_env)
{
    
}*/

int ft_find_name(char *var, t_env *env, int op)
{
    int i;
    char *name;

    i = ft_varlen(var, 0);
    if (!(name = malloc(sizeof(char) * i + 1)))
        return (-1);
    ft_strlcpy(name, var, i + op - 1);
    printf("name=%s\n", name);
    i++;
    while (env)
    {
        if (ft_strcmp(name, env->name) == 0)
        {
            free(name);
            return (ft_export_edit(var + i, env, op));
        }
        env = env->next;
    }
    free(name);
    return (0);
    //return (ft_export_new(var, env));
}

/*
** RETURN =-1 : ERREUR
** RETURN = 0 : NO OP
** RETURN = 1 : OP = "="
** RETURN = 2 : OP = "+="
*/
int ft_check_name(char *var)
{
    int i;

    i = 0;
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
        else
            return (ft_put_error("not a valid identifier", var, 1));
    }
    return (0);
}

int ft_tablen(char **tab)
{
    int len;

    len = 0;
    while (tab[len] != NULL)
        len++;
    return (len);
}

void free_tab(char **tab)
{
    int i;

    i = 0;
    if (tab)
    {
        while (tab[i])
            free(tab[i++]);
    }
}

char **tab_dup(char **tab)
{
    int i;
    char **new;

    i = 0;
    new = NULL;
    if (!(new = malloc(sizeof(char *) * ft_tablen(tab))))
        return (NULL);
    while (tab[i])
    {
        new[i] = ft_strdup(tab[i]);
        i++;
    }
    new[i] = 0;
    return (new);
}

void ft_putenv(char **env)
{
    int i;

    i = 0;
    while (env[i] != 0)
    {
        ft_putstr_fd(env[i++], 1);
        write(1, "\n", 1);
    }
}

void ft_export_null(char **env)
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
}

char **ft_export_core(char *var, char **env)
{
    int i;
    int j;
    int op;
    int len;
    t_env *lst;

    i = 0;
    j = 0;
    len = ft_tablen(env);
    if (var == NULL)
        ft_export_null(env);
    if ((op = ft_check_name(var)) < 1)
        return (env);
    lst = ft_tab_to_list(env);
    ft_find_name(var, lst, op);
    env = ft_list_to_tab(lst);
/*    for (int x=0;env[x];x++)
        printf("env[%d]=%s\n", x, env[x]);*/
    //AJOUTER FREE DE LA LISTE PRECEDENTE
    return (env);
}

char *ft_getenv(char *var, char **env)
{
    int i;
    int j;
    char *value;

    i = 0;
    value = NULL;
    if (env == NULL || var == NULL)
        return (NULL);
    while (env[i] != NULL)
    {
        j = 0;
        if (!(ft_strncmp(var, env[i], ft_strlen(var))))
        {
            while (env[i][j] != '=')
                j++;
            value = ft_strdup(env[i] + (j + 1));
            break;
        }
        i++;
    }
    return (value);
}