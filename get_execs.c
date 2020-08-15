/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:23:06 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/15 18:29:30 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_exec(t_all *all, DIR *dir)
{
    struct dirent *sd;

    sd = NULL;
    if (dir)
    {
        while ((sd = readdir(dir)) != NULL)
        {
            //printf("sd->d_name=%s\n", sd->d_name);
            if (ft_strcmp(all->dir[1], sd->d_name) == 0) // a changer en 1 plus tard
            {
                printf("-----------------------------program %s found as %s\n", all->dir[1], sd->d_name); // ajouter le slash entre le path et l'exec
                return (1);
            }
        }
    }
    return (0);
}

int get_path(t_all *all)
{
    int             i;
    DIR             **dir;
    char            **path;

    i = 0;
    path = ft_split(ft_getenv("PATH", all->env), ':');
    while (path[i] != 0)
        i++;
    dir = malloc(sizeof(DIR) * (i + 1));
    i = 0;
    if (path)
    {
        while (path[i] != 0)
        {
            dir[i] = opendir(path[i]);
            printf("dir[%d]=%s\n", i, path[i]);
            find_exec(all, dir[i]);
            i++;
        }
    }
    free_tab(path);
    return (0);
}