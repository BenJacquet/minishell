/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 12:35:39 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/07 17:02:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_find_name(char *var, t_env *env)
{
    int i;

    i = 0;
    while (var[i] != '=' || ft_strncmp(var + i, "+=", 2))
        i++;
    while (env)
    {
        if (ft_strncmp(var, env->name, i))
            return (1);
        env = env->next;
    }
    return (0);
}

int ft_check_name(char *var) // verifier si le nom ne comprend pas de chars interdits, osef de la value
{
    int i;

    i = 0;
    if (var[i] != '\0')
    {
        if (ft_isdigit(var[i]) || var[i] == '=')
            return (ft_put_error("not a valid identifier", var, 1));
        while (ft_isalnum(var[i]) || var[i] == '_')
            i++;
        if (var[i] != '=' || ((ft_strncmp(var + i, "+=", 2) &&
            var[i + 1] != '\0' && var[i + 1] != '=')))
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
    while (env[i] != NULL)
    {
        ft_putstr_fd(env[i++], 1);
        write(1, "\n", 1);
    }
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

int ft_export_core(char *var, char **env)
{
    int i;
    int j;
    int len;
    t_env *lst;

    i = 0;
    j = 0;
    len = ft_tablen(env);
    if (var == NULL)
        return (ft_export_null(env));
    if (ft_check_name(var))
        return (-1);
    lst = ft_tab_to_list(env);
    if (!(ft_find_name(var, lst)))
        return (0);
    return (0);
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