/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 12:35:39 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/05 16:59:36 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** RETURN 0
**
*/
/*int ft_add_var(char *var, char *env)
{
    ft_strncmp() if () return (1);
    return (0);
}*/

char *ft_find_var(char *var, char **env)
{
    int j;

    j = 0;
    while (env[j] != NULL)
    {
        if (ft_strcmp(var, env[j]))
        {
            env = ft_strdup(var);
            return (1);
        }
    }
}

int ft_envlen(char **env)
{
    int len;

    len = 0;
    while (env[len] != NULL)
        len++;
    return (len);
}

char **ft_sort_tab(char **env)
{
    int i;
    int j;
    char **sorted;

    i = 0;
    j = 0;
    if (!(sorted = malloc(sizeof(char*) * ft_envlen(env))))
        return (NULL);
    while(env[i])
    {
        if (env[i + 1] && j == i)
            j++;
        if (ft_strcmp(env[i], env[j]) > 0)
            sorted[i] = env[j];
        i++;
    }
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

int ft_export(char *var, char **env)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    len = ft_envlen(env);
    if (var == NULL)
    {
        ft_putenv(ft_sort_tab(env));
        return (0);
    }
    while (var[i] != '\0')
    {
        if (var[i] == '=')
        {
            while (env[j] != NULL/* && !ft_find_var(var, env[j], i)*/)
                j++;
            env[j] = ft_strdup(var);
            env[len] = NULL;
            printf("len = %d\n", len);
            break;
        }
        i++;
    }
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