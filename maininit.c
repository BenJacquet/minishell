/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maininit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:15:04 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/22 15:13:19 by jabenjam         ###   ########.fr       */
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
	all->i = all->i;
	(signal(SIGQUIT, &handle));
	(signal(SIGINT, &handle));
//	if (g_freete == 1)
//		all->countpipe = -666; // pour eviter le commande not found
	return (0);
}

void		init_allbis(t_all *all, char **env, int ac, char **av)
{
	get_dir();
	(void)ac;
	(void)av;
	g_freete = 0;
	g_builtin = 0;
	all->here = 0;
	signal_manager(all);
	all->toks = NULL;
	all->reds = NULL;
	all->fds[0] = STDIN_FILENO;
	all->fds[1] = STDOUT_FILENO;
	all->mask = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	all->i = get_next_line(0, &all->buff);
	crontold(all);
	if (checkquote(all->buff) == 1)
		write(1, "No Multilines\n", 14);
	all->env = ft_tab_to_list(env, 0);
	all->env_replaced = 0;
	all->ret = new_elem("?=0");
	all->red = 0;
	all->cmd = 0;
}

void		init_all(t_all *all, char **env, int ac, char **av)
{
	init_allbis(all, env, ac, av);
	all->countpipe = (g_freete == 0) ? pipecount(*all, all->buff, ';') + 1 : 0;
	all->pdir = ft_splitmini(all->buff, ';');
	all->tube = (g_freete == 0 && all->pdir[0] && all->countpipe > 0) ?
				pipecount(*all, all->pdir[0], '|') : 0;
	all->countpipe = (all->tube >= 0) ? all->countpipe : 0;
	all->data = all->countpipe;
	all->xdir = ft_splitmini(all->pdir[0], '|');
	all->dir = ft_split(all->buff, ' ');
}
