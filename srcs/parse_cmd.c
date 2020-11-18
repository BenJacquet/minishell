/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:21:37 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/17 17:40:34 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		commands(t_all *all)
{
	if (ft_strcmp(all->dir[0], "cd") == 0)
		update_return(all, cd(all->dir, all));
	else if (ft_strcmp(all->dir[0], "pwd") == 0)
		update_return(all, pwd(all->buff));
	else if (ft_strcmp(all->dir[0], "echo") == 0)
		update_return(all, echo(*all));
	else if (ft_strcmp(all->dir[0], "export") == 0)
		ft_export_core(all);
	else if (ft_strcmp(all->dir[0], "unset") == 0)
		ft_unset_core(all);
	else if (ft_strcmp(all->dir[0], "env") == 0)
		ft_putenv(all);
	else
	{
		all->exec = get_path(all);
		g_builtin = 2;
		run_exec(all);
	}
	return (1);
}

int		run_command(t_all *all, int fd[all->tube][2])
{
	all->toks = convert_tokens_lst(all->dir, all->shouldi);
	if (all->countsmc)
		handle_redirections(all);
	all->dir = convert_tokens_tab(all->toks);
	io_manager_dup_replace(all, fd, 0);
	commands(all);
	io_manager_dup_restore(all);
	if (all->tube)
		pipes_parent(all, fd);
	reset_fds(all);
	return (0);
}

int		parse_command(t_all *all, int fd[all->tube][2])
{
	if (all->pdir[all->data - all->countsmc] &&
			ft_strlen(all->pdir[all->data - all->countsmc]) > 0)
	{
		if (!all->tube)
			joinquote(all);
		if (!all->dir[0] || ft_strlen(all->dir[0]) == 0)
			return (1);
		return (fork_or_not(all, fd));
	}
	else
		return (1);
	return (0);
}

int		action(t_all *all, int fd[all->tube][2])
{
	if (all->countsmc > 0)
	{
		parse_command(all, fd);
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
