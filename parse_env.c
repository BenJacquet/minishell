/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 12:35:39 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/05 14:38:17 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char     *ft_getenv(char *var, char **env)
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