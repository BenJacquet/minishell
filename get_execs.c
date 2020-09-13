/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 15:23:06 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/13 18:25:56 by jabenjam         ###   ########.fr       */
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

char *get_path(t_all *all, char **envp)
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
	if (all->dir && all->dir[0] && all->dir[0][0] == '.')
		run_exec(all, is_exec(all), all->dir, envp);
	else
		path = ft_split(ft_getenv(all, "PATH"), ':');
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

/*
** MODE = 1 : REMPLACEMENT DE STDIN/STDOUT PAR LE FD
** MODE = 2 : RESTAURATION DE STDIN/STDOUT
*/

int	io_manager_dup(t_all *all, int mode)
{
	if (mode == 1)
	{
		if (all->red == 2)
		{
			dup2(all->fd, STDIN_FILENO);
			close(all->fd);
		}
		else if (all->red == 522 || all->red == 1538)
		{
			dup2(all->fd, STDOUT_FILENO);
			close(all->fd);
		}
	}
	else
	{
		if (all->red == 2)
			dup2(0, STDIN_FILENO);
		else if (all->red == 522 || all->red == 1538)
			dup2(1, STDOUT_FILENO);
	}
	return (0);
}

int run_exec(t_all *all, char *exec, char **args, char **envp)
{
	int ret;
	pid_t child_pid;

	ret = 0;
	envp = ft_list_to_tab(all->env, 0);
	if (all->red == 522 || all->red == 1538 || all->red == 2)
		all->fd = open("text.txt", all->red);
	printf("all->fd=%d\n", all->fd);
	if ((child_pid = fork()) == 0)
	{
		io_manager_dup(all, 1);
		if (all->red == 2 && all->fd != -1)
			execve(exec, args, envp);
		else
			execve(exec, args, envp);
		io_manager_dup(all, 2);
	}
	else
	{
		if (all->red)
			close(all->fd);
		waitpid(child_pid, &ret, 0);
	}
	all->ret->value = ft_itoa(ret / 256);
	printf("all->ret->value=%s\n", all->ret->value);
	free_tab(envp);
	return (1);
}