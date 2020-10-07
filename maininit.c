/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maininit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:15:04 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/07 18:10:00 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handle(int sig)
{
	if (sig == SIGINT)
	{
		if (builtin != 2)
			write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
		if (builtin == 0)
			get_dir();
	}
	else if (sig == SIGQUIT)
	{
		if (builtin == 2)
			write(1, "Quit: 3\n", 8);
		else
			write(1, "\b\b  \b\b", 6);
	}
}

int			signal_manager(void)
{
	(signal(SIGINT, &handle));
	(signal(SIGQUIT, &handle));
	return (0);
}

void		init_all(t_all *all, char **env, int ac, char **av)
{
	get_dir();
	(void)ac;
	(void)av;
	signal_manager();
	all->toks = NULL;
	all->reds = NULL;
	builtin = 0;
	all->fds[0] = STDIN_FILENO;
	all->fds[1] = STDOUT_FILENO;
	all->mask = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	all->i = get_next_line(0, &all->buff);
	crontold(all);
	all->env = ft_tab_to_list(env);
	all->ret = new_elem("?=0");
	all->countpipe = pipecount(*all, all->buff, ';') + 1;
	all->data = all->countpipe;
	all->pdir = (all->countpipe > 1) ?
		ft_splitmini(all->buff, ';') : ft_split(all->buff, '\0');
	all->dir = ft_split(all->buff, ' ');
	all->ret->value = ft_itoa(0);
	all->reds = NULL;
}
