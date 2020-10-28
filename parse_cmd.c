/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:21:37 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/28 18:33:35 by jabenjam         ###   ########.fr       */
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

int		fork_command(t_all *all, char **env, int fd[all->tube][2])
{
	int		pid;
	int		ret;

	pid = 0;
	all->toks = convert_tokens_lst(all->dir, all->shouldi);
	if (all->countsmc)
		handle_redirections(all);
	all->dir = convert_tokens_tab(all->toks);
	if ((pid = fork()) == 0)
	{
		io_manager_dup_replace(all, fd, 1);
		parse_command2(all);
		io_manager_dup_restore(all);
		exit(freelance(all, env));
	}
	else
	{
		waitpid(pid, &ret, 0);
		update_return(all, ret / 256);
		if (all->tube)
			pipes_parent(all, fd);
		reset_fds(all);
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

int		fork_or_not(t_all *all, char **env, int fd[all->tube][2])
{
	if (ft_strcmp(all->dir[0], "unset") == 0 ||
		(ft_strcmp(all->dir[0], "export") == 0 && ft_tablen(all->dir) > 1)||
		ft_strcmp(all->dir[0], "cd") == 0)
	{
		write(2, "RUN_COMMAND\n", 12);
		return (run_command(all, env, fd));
	}
	else
	{
		write(2, "FORK_COMMAND\n", 13);
		return (fork_command(all, env, fd));
	}
	return (0);
}

int		parse_command(t_all *all, char **env, int fd[all->tube][2])
{
	if (all->pdir[all->data - all->countsmc] &&
			ft_strlen(all->pdir[all->data - all->countsmc]) > 0)
	{
		if (!all->tube)
			joinquote(all);
		if (!all->dir[0] || ft_strlen(all->dir[0]) == 0)
			return (1);
		return (fork_or_not(all, env, fd));
	}
	else
		return (1);
	return (0);
}
