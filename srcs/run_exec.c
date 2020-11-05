/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:46:15 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/05 22:19:13 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
