/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:23:06 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/28 16:17:49 by jabenjam         ###   ########.fr       */
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
	struct dirent *sd;

	sd = NULL;
	if (dir)
	{
		while ((sd = readdir(dir)) != NULL)
		{
			if (ft_strcmp(all->dir[all->i - 1], sd->d_name) == 0)
			{
				//printf("sd->d_type=%d\n", sd->d_type);
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
		if (ft_strncmp(all->dir[0], ".", 1) == 0 ||
			ft_strncmp(all->dir[0], "/", 1) == 0)
			return (all->dir[0]);
		else
			return (NULL);
	}
	return (NULL);
}

char *get_path(t_all *all)
{
	int i;
	DIR **dir;
	char **path;
	char *exec;

	i = 0;
	exec = NULL;
	path = NULL;
	if (!all->dir || !all->dir[0])
		return (0);
	if (all->dir && all->dir[0] && (all->dir[0][0] == '.' || all->dir[0][0] == '/'))
		return (is_exec(all));
	else
		path = ft_split(ft_getenv(all, "PATH", 0), ':');
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
				break;
			i++;
		}
	}
	free_tab(path);
	return (exec);
}

int run_exec(t_all *all, char *exec, char **args, char **envp)
{
	int ret;
	int	status;
	pid_t child_pid;

	ret = 0;
	status = 0;
	envp = ft_list_to_tab(all->env, 0);
	//printf("all->fd=%d\n", all->fd);
	if ((child_pid = fork()) == 0)
	{
		//printf("\033[1;31m-----------------\nLAST_RED:\nfilename=[%s]\nred=[%d]\nfd=[%d]\n-----------------\n\033[0m", all->reds->filename, all->reds->red, all->reds->fd);
		status = execve(exec, args, envp);
		if (status == -1)
			ft_put_error(strerror(errno), exec, 1);
	}
	else
		waitpid(child_pid, &ret, 0);
	all->ret->value = ft_itoa(ret / 256);
	//printf("all->ret->value=%s\n", all->ret->value);
	free_tab(envp);
	return (1);
}