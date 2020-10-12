/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maininit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:15:04 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/12 17:16:44 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handle(int sig)
{
	if (sig == SIGINT)
	{
		if (g_builtin != 2)
			write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
		if (g_builtin == 0)
			get_dir();
		g_freete = 1;
	}
	else if (sig == SIGQUIT)
	{
		if (g_builtin == 2)
			write(1, "Quit: 3\n", 8);
		else
			write(1, "\b\b  \b\b", 6);
	}
}

int			signal_manager(t_all *all)
{
	(signal(SIGQUIT, &handle));
	(signal(SIGINT, &handle));
	if (g_freete == 1)
		all->countpipe = 0;
	return (0);
}

void		init_allbis(t_all *all, char **env, int ac, char **av)
{
	get_dir();
	(void)ac;
	(void)av;
	g_freete = 0;
	g_builtin = 0;
	signal_manager(all);
	all->toks = NULL;
	all->reds = NULL;
	all->fds[0] = STDIN_FILENO;
	all->fds[1] = STDOUT_FILENO;
	all->mask = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	all->i = get_next_line(0, &all->buff);
	crontold(all);
	all->env = ft_tab_to_list(env);
	all->ret = new_elem("?=0");

}
void		init_all(t_all *all, char **env, int ac, char **av)
{
	init_allbis(all, env, ac, av);
	all->countpipe = (g_freete == 0) ? pipecount(*all, all->buff, ';') + 1 : 0;
	all->pdir = NULL;
	all->pdir = ft_splitmini(all->buff, ';');
	all->tube = (g_freete == 0 && all->pdir[0] && all->countpipe > 0) ? pipecount(*all, all->pdir[0], '|') : 0;
	all->xdir = NULL;
	all->countpipe = (all->tube >= 0) ? all->countpipe : 0;
	all->data = all->countpipe;
	all->xdir = ft_splitmini(all->pdir[0], '|');
	all->dir = ft_split(all->buff, ' ');
	all->ret->value = ft_itoa(0);
	all->reds = NULL;
}
