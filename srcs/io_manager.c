/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:49:52 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/26 18:06:22 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	reset_fds(t_all *all)
{
	all->fds[0] = STDIN_FILENO;
	all->fds_backup[0] = STDIN_FILENO;
	all->fds[1] = STDOUT_FILENO;
	all->fds_backup[1] = STDOUT_FILENO;
}

int		no_command(t_all *all, int mode)
{
	if (mode == 1)
	{
		if (all->fds[0] != 0)
			close(all->fds[0]);
		if (all->fds[1] != 1)
			close(all->fds[1]);
	}
	return (0);
}

int		io_manager_dup_replace(t_all *all, int fd[all->tube][2], int fork)
{
	if (!all->dir[0])
		return (no_command(all, 1));
	if (all->fds[0] != 0)
	{
		all->fds_backup[0] = dup(STDIN_FILENO);
		dup2(all->fds[0], STDIN_FILENO);
		close(all->fds[0]);
	}
	if (all->fds[1] != 1)
	{
		all->fds_backup[1] = dup(STDOUT_FILENO);
		dup2(all->fds[1], STDOUT_FILENO);
		close(all->fds[1]);
	}
	if (all->tube && fork)
		pipes_child(all, fd);
	return (0);
}

int		io_manager_dup_restore(t_all *all)
{
	if (!all->dir[0])
		return (no_command(all, 0));
	if (all->fds[0] != 0)
	{
		dup2(all->fds_backup[0], STDIN_FILENO);
		close(all->fds_backup[0]);
	}
	if (all->fds[1] != 1)
	{
		dup2(all->fds_backup[1], STDOUT_FILENO);
		close(all->fds_backup[1]);
	}
	return (0);
}
