/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:26:01 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/17 18:27:57 by jabenjam         ###   ########.fr       */
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

char *remove_space(char *str)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (!(new = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (NULL);
    //printf("str=%s\n", str);
    while (str[j] != '\0')
    {
        while (str[j] != '\0' && str[j] == ' ' && i == 0)
        {
            printf("str[%d+%d]=%d\n", i, j, str[i+j]);
            j++;
        }
        while (str[j] != '\0' && str[j] != ' ')
            new[i++] = str[j++];
        if (str[j] != '\0' && str[j] == ' ' && (j) < ft_strlen(str))
        {
            new[i++] = ' ';
            while (str[j] != '\0' && str[j] == ' ')
            j++;
        }
    }
    new[i] = '\0';
    free(str);
    printf("new=%s\n",new);
    return (new);
}

char *ft_getenv(char *var, char **env)
{
    int i;
    int j;
    char *value;

    i = 0;
    value = NULL;
    printf("var=%s\n", var);
    if (env == NULL || var == NULL)
        return (NULL);
    while (env[i] != NULL)
    {
        j = 0;
        if (!(ft_strncmp(var, env[i], ft_strlen(var))))
        {
            while (env[i][j] != '=')
                j++;
            value = remove_space(ft_strdup(env[i] + (j + 1)));
            break;
        }
        i++;
    }
    return (value);
}