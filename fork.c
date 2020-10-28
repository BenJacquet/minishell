/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:58:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/28 19:21:22 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	elsefork(t_all *all, char **env, int fd[all->tube][2])
{
	waitpid(all->pid, &all->retpid, 0);
	signal_manager();
	update_return(all, all->retpid / 256);
	if (all->tube)
		pipes_parent(all, fd);
	reset_fds(all);
}

int		fork_command(t_all *all, char **env, int fd[all->tube][2])
{
	all->pid = 0;
	all->toks = convert_tokens_lst(all->dir, all->shouldi);
	if (all->countsmc)
		handle_redirections(all);
	all->dir = convert_tokens_tab(all->toks);
	if ((all->pid = fork()) == 0)
	{
		io_manager_dup_replace(all, fd, 1);
		parse_command2(all);
		io_manager_dup_restore(all);
		exit(freelance(all, env));
	}
	else
		elsefork(all, env, fd);
	return (0);
}

int		fork_or_not(t_all *all, char **env, int fd[all->tube][2])
{
	if (ft_strcmp(all->dir[0], "unset") == 0 ||
		(ft_strcmp(all->dir[0], "export") == 0 && ft_tablen(all->dir) > 1) ||
		ft_strcmp(all->dir[0], "cd") == 0)
	{
		write(2, "RUN_COMMAND\n", 12);
		return (run_command(all, env, fd));
	}
	else
	{
		write(2, "FORK_COMMAND\n", 13);
		g_builtin = 2;
		if (ft_strcmp(all->dir[0], "./minishell") == 0 ||
				ft_strncmp(all->dir[0], "man", 3) == 0)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
		}
		return (fork_command(all, env, fd));
	}
	return (0);
}
