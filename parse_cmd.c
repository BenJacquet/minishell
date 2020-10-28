/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:21:37 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/28 19:26:07 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtins(t_all *all)
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
		ft_putenv(all->env);
	return (1);
}

int		is_binary(t_all *all)
{
	run_exec(all);
	return (0);
}

int		parse_command2(t_all *all)
{
	int here;

	here = all->data - all->countsmc;
	if (all->dir[0] &&
			((ft_strcmp(all->dir[0], "cd") == 0) ||
			ft_strcmp(all->dir[0], "pwd") == 0 ||
			ft_strcmp(all->dir[0], "echo") == 0 ||
			ft_strcmp(all->dir[0], "env") == 0 ||
			ft_strcmp(all->dir[0], "unset") == 0 ||
			ft_strcmp(all->dir[0], "export") == 0))
		return (builtins(all));
	else if ((all->exec = get_path(all)) != NULL)
	{
		g_builtin = 2;
		is_binary(all);
		return (1);
	}
	return (0);
}

int		run_command(t_all *all, char **env, int fd[all->tube][2])
{
	all->toks = convert_tokens_lst(all->dir, all->shouldi);
	if (all->countsmc)
		handle_redirections(all);
	all->dir = convert_tokens_tab(all->toks);
	io_manager_dup_replace(all, fd, 0);
	parse_command2(all);
	io_manager_dup_restore(all);
	if (all->tube)
		pipes_parent(all, fd);
	reset_fds(all);
	return (0);
}

int		parse_command(t_all *all, char **env, int fd[all->tube][2])
{
	if (all->pdir[all->data - all->countsmc] &&
			ft_strlen(all->pdir[all->data - all->countsmc]) > 0)
	{
		if (!all->tube)
			joinquote(all);
		tokentranslate(all, &*all->dir);
		if (!all->dir[0] || ft_strlen(all->dir[0]) == 0)
			return (1);
		return (fork_or_not(all, env, fd));
	}
	else
		return (1);
	return (0);
}
