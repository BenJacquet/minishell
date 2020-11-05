/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:46:15 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/28 19:57:18 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
**	MODE 0 : Si le dernier char est un '/'
**	MODE 1 : Si la string contient un '/'
*/

int		slash(char	*str, int mode)
{
	int		i;

	i = (mode == 0 ? ft_strlen(str) : 0);
	if (i > 0 && mode == 0)
	{
		if (str[i - 1] == '/' || str[i - 1] == '.')
			return (1);
	}
	else if (mode == 1)
	{
		while (str[i])
		{
			if (str[i] == '/')
				return (1);
			i++;
		}
	}
	return (0);
}

int		get_error(t_all *all)
{
	if (ft_strcmp(all->dir[0], ".") == 0)
	{
		ft_put_error(
		"filename argument required\n.: usage: . filename [arguments]",
		all->dir[0], 1);
		return (2);
	}
	if (errno == 13 && slash(all->dir[0], 0))
	{
		errno = 21;
		return (-126);
	}
	else if (errno == 2 || errno == 13)
	{
		if (slash(all->dir[0], 1))
			return (-127);
		ft_put_error("command not found", all->dir[0], 1);
		return (127);
	}
	return (-1);
}

int		check_execution(t_all *all, char **envp)
{
	char **tmp;
	if (ft_strcmp(all->dir[0], "\0") == 0)
		return (0);
	else if (all->bad && ft_tablen(all->dir) == 1 &&
			ft_strcmp(all->dir[0], "cat") == 0)
	{
		if (all->bad->exists == 0)
			return (0);
		if (!(tmp = malloc(sizeof(char*) * (3))))
			return (0);
		tmp[0] = ft_strdup(all->dir[0]);
		tmp[1] = ft_strdup(all->bad->file);
		tmp[2] = NULL;
		execve(all->exec, tmp, envp);
		free_tab(tmp);
		return (1);
	}
	else if (all->bad)
	{
		if (all->bad->red == I_R && all->bad->exists)
			return (execve(all->exec, all->dir, envp));
		return (0);
	}
	return (execve(all->exec, all->dir, envp));
}

int		bad_red(t_all *all)
{
	if (all->bad->red != I_R)
		return (ft_put_error(strerror(21), all->bad->file, 1));
	else if (all->bad->red == I_R && !all->bad->exists)
		return (ft_put_error(strerror(2), all->bad->file, 1));
	else if (all->bad->red == I_R &&
			(ft_strcmp(all->dir[0], "\0") != 0 || ft_tablen(all->dir) > 1))
		return (ft_put_error(strerror(21), all->bad->file, 1));
	return (0);
}

int		run_exec(t_all *all)
{
	int		ret;
	int		status;
	char	**envp;

	ret = 0;
	status = 0;
	envp = ft_list_to_tab(all->env, 0, 0);
	status = check_execution(all, envp);
	if (status == -1 || all->bad)
	{
		if (all->bad)
			ret = bad_red(all);
		else if ((ret = get_error(all)) < 0)
			ft_put_error(strerror(errno), all->dir[0], 1);
		update_return(all, ft_abs(ret));
	}
	free_tab(envp);
	return (1);
}

int		action(t_all *all, int fd[all->tube][2])
{
	if (all->countsmc > 0)
	{
		parse_command(all, fd);
		free(all->shouldi);
		g_builtin = 0;
	}
	return (0);
}

int		multidir(t_all *all, int fd[all->tube][2])
{
	all->here = 0;
	while (all->here <= all->tube)
	{
		joinquotev2(all);
		if (all->here == 0)
			all->around = 1;
		else if (all->here == all->tube)
			all->around = 0;
		else
			all->around = 2;
		action(all, fd);
		all->bad = free_red(all->bad);
		all->here++;
	}
	all->countsmc--;
	all->tube = 0;
	return (0);
}
