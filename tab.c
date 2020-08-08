/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 18:06:32 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/08 18:31:13 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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