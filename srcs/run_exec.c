/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:46:15 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/24 22:50:24 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		get_error(t_all *all)
{
	if (ft_strcmp(all->dir[0], ".") == 0)
	{
		ft_put_error(
		"filename argument required\n.: usage: . filename [arguments]",
		all->dir[0], 0, 1);
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
		ft_put_error("command not found", all->dir[0], 0, 1);
		return (127);
	}
	return (-1);
}

int		bad_red(t_all *all)
{
	if (all->bad)
	{
		if (all->bad->red != I_R)
			ft_put_error(strerror(21), all->bad->file, 0, 1);
		else if (all->bad->red == I_R && !all->bad->exists)
			ft_put_error(strerror(2), all->bad->file, 0, 1);
		else if (all->bad->red == I_R &&
				(ft_strcmp(all->dir[0], "\0") != 0 || ft_tablen(all->dir) > 1))
			ft_put_error(strerror(21), all->bad->file, 0, 1);
		update_return(all, 1);
		return (1);
	}
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
	status = execve(all->exec, all->dir, envp);
	if (status == -1)
	{
		if ((ret = get_error(all)) < 0)
			ft_put_error(strerror(errno), all->dir[0], 0, 1);
		update_return(all, ft_abs(ret));
	}
	free_tab(envp);
	return (1);
}
