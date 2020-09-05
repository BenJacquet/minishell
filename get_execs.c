/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:23:06 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/05 18:11:56 by jabenjam         ###   ########.fr       */
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
                printf("sd->d_type=%d\n", sd->d_type);
                closedir(dir);
                return (make_exec(all, path));
            }
        }
        closedir(dir);
    }
    return (NULL);
}

char *is_exec(t_all *all)
{
    if (all->dir)
    {
        if (ft_strncmp(all->dir[0], "./", 2) == 0 ||
            ft_strncmp(all->dir[0], "../", 3) == 0)
        {
            return (all->dir[0]);
        }
        else
            return (NULL);
    }
    return (NULL);
}

char *get_path(t_all *all, char **env)
{
    int             i;
    DIR             **dir;
    char            **path;
    char            *exec;

    i = 0;
    exec = NULL;
    path = NULL;
    if (!all->dir || !all->dir[0])
        return (0);
    if (all->dir && all->dir[0] && all->dir[0][0] == '.')
        run_exec(is_exec(all), all->dir, env);
    else
        path = ft_split(ft_getenv("PATH", ft_list_to_tab(all->env, 0)), ':');
    if (path)
    {
        while (path[i] != NULL)
            i++;
    }
    if (!(dir = malloc(sizeof(DIR*) * (i + 1))))
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
    return (exec);
}

int run_exec(char *exec, char **args, char **envp)
{
    pid_t child_pid;
    if ((child_pid = fork()) == 0)
    {
        printf("parent pid=%d\n", getppid());
        printf("child pid=%d\n", getpid());
        execve(exec, args, envp);
    }
    else
        waitpid(child_pid, 0, 0);
    return (1);
}