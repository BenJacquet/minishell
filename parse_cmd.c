/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:21:37 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/25 15:52:54 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtins_others(t_all *all)
{
	int	pipe_bkp;

	pipe_bkp = all->countpipe;
	if (ft_strcmp(all->dir[0], "cd") == 0)
	{
		update_return(all, cd(all->dir, *all));
		all->countpipe--;
	}
	else if (ft_strcmp(all->dir[0], "pwd") == 0)
	{
		update_return(all, pwd(all->buff));
		all->countpipe--;
	}
	else if (ft_strcmp(all->dir[0], "echo") == 0)
	{
		update_return(all, echo(*all));
		all->countpipe--;
	}
	return (all->countpipe != pipe_bkp ? 1 : 0);
}

int		builtins_env(t_all *all)
{
	int	pipe_bkp;

	pipe_bkp = all->countpipe;
	if (ft_strcmp(all->dir[0], "export") == 0)
	{
		ft_export_core(all);
		all->countpipe--;
	}
	else if (ft_strcmp(all->dir[0], "unset") == 0)
	{
		ft_unset_core(all);
		all->countpipe--;
	}
	else if (ft_strcmp(all->dir[0], "env") == 0)
	{
		ft_putenv(all->env);
		all->countpipe--;
	}
	return (all->countpipe != pipe_bkp ? 1 : 0);
}

int		is_binary(t_all *all)
{
	if (all->tube)
		run_exec_forked(all, all->exec, all->dir);
	else
		run_exec(all, all->exec, all->dir);
	return (0);
}

int		parse_command2(t_all *all)
{
	int here;

	here = all->data - all->countpipe;
	if (all->dir[0] &&
			((ft_strcmp(all->dir[0], "cd") == 0) ||
			ft_strcmp(all->dir[0], "pwd") == 0 ||
			ft_strcmp(all->dir[0], "echo") == 0))
		return (builtins_others(all));
	else if (all->dir[0] &&
			((ft_strcmp(all->dir[0], "env") == 0) ||
			ft_strcmp(all->dir[0], "unset") == 0 ||
			ft_strcmp(all->dir[0], "export") == 0))
		return (builtins_env(all));
	else if ((all->exec = get_path(all)) != NULL)
	{
		g_builtin = 2;
		is_binary(all);
		all->countpipe--;
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
	if (all->countpipe)
		handle_redirections(all);
	all->dir = convert_tokens_tab(all->toks);
	if ((pid = fork()) == 0)
	{
		io_manager_dup_replace(all, fd);
		if (!parse_command2(all))
			writenotfound(all);
		io_manager_dup_restore(all);
		exit(freelance(all, env));
	}
	else
	{
		waitpid(pid, &ret, 0);
		update_return(all, ret / 256);
		reset_fds(all);
		if (all->tube)
			pipes_parent(all, fd);
	}
	return (0);
}

int		parse_command(t_all *all, char **env, int fd[all->tube][2])
{
	if (all->pdir[all->data - all->countpipe] &&
			ft_strlen(all->pdir[all->data - all->countpipe]) > 0)
	{
		if (!all->tube)
			joinquote(all);
		if (!all->dir[0] || ft_strlen(all->dir[0]) == 0)
		{
			all->countpipe--;
			return (1);
		}
		return (fork_command(all, env, fd));
	}
	else
	{
		all->countpipe--;
		return (1);
	}
	return (0);
}
