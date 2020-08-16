/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:23:06 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/16 18:47:51 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *make_exec(t_all *all, char *path)
{
    char *exec;
    char *bkp;

    exec = ft_strdup(path);
    bkp = exec;
    exec = ft_strjoin(exec, "/");
    free(bkp);
    bkp = exec;
    exec = ft_strjoin(exec, all->dir[all->i - 1]);
    free(bkp);
    return (exec);
}

char *find_exec(t_all *all, DIR *dir, char *path)
{
    struct dirent   *sd;

    sd = NULL;
    if (dir)
    {
        while ((sd = readdir(dir)) != NULL)
        {
            if (ft_strcmp(all->dir[all->i - 1], sd->d_name) == 0)
            {
                closedir(dir);
                return (make_exec(all, path));
            }
        }
        closedir(dir);
    }
    return (NULL);
}

char *get_path(t_all *all)
{
    int             i;
    DIR             **dir;
    char            **path;
    char            *exec;

    i = 0;
    exec = NULL;
    path = ft_split(ft_getenv("PATH", ft_list_to_tab(all->env)), ':');
    if (path)
    {
        while (path[i] != NULL)
        i++;
    }
    if (!(dir = malloc(sizeof(DIR) * (i + 1))))
        return (NULL);
    i = 0;
    if (path)
    {
        while (path[i] != NULL)
        {
            dir[i] = opendir(path[i]);
            if ((exec = find_exec(all, dir[i], path[i])))
                break;
            i++;
        }
    }
    free_tab(path);
    printf("exec=%s\n", exec);
    return (exec);
}

int run_exec(char *exec, char **args, char **envp)
{
    //int pid;
    for (int i=0; args[i]; i++)
        printf("args[%d]=%s\n", i, args[i]);
    //pid = fork();
    execve(exec, args, envp);
    return (1);
}