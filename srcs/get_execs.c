/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:23:06 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/28 19:45:18 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*make_exec(t_all *all, char *path)
{
	char	*exec;

	exec = ft_strdup(path);
	exec = ft_strjoinf(exec, "/");
	exec = ft_strjoinf(exec, all->dir[all->i - 1]);
	return (exec);
}

char	*find_exec(t_all *all, DIR *dir, char *path)
{
	struct dirent	*sd;

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

char	*find_dir(t_all *all, char **path, DIR **dir)
{
	char	*exec;
	int		i;

	i = 0;
	exec = NULL;
	if (path)
	{
		while (path[i] != NULL)
			i++;
	}
	if (!(dir = malloc(sizeof(DIR *) * (i + 1))))
		return (NULL);
	i = 0;
	if (path)
	{
		while (path[i] != NULL)
		{
			dir[i] = opendir(path[i]);
			if ((exec = find_exec(all, dir[i], path[i])))
				break ;
			i++;
		}
	}
	free(dir);
	return (exec);
}

char	*get_path(t_all *all)
{
	DIR		**dir;
	char	**path;
	char	*exec;

	path = NULL;
	dir = NULL;
	if (!all->dir || !all->dir[0])
		return (NULL);
	path = ft_splitf(ft_getenv(all, "PATH", 0), ':');
	if ((exec = find_dir(all, path, dir)) == NULL)
		exec = ft_strdup(all->dir[0]);
	free_tab(path);
	return (exec);
}
