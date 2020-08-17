/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:26:01 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/16 18:05:06 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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