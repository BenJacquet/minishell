/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maininit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:31:58 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/21 19:52:03 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		handle(int sig)
{
	if (sig == SIGINT)
	{
		if (g_builtin != 2)
			write(1, "\b\b  \b\b", 6);
		write(1, "\n", 1);
		if (g_builtin == 0)
			get_dir_sig();
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

int			signal_manager(void)
{
	(signal(SIGQUIT, &handle));
	(signal(SIGINT, &handle));
	return (0);
}

void		init_allbis(t_all *all, char **env, int ac, char **av)
{
	get_dir(all);
	(void)ac;
	(void)av;
	g_freete = 0;
	g_builtin = 0;
	all->here = 0;
	signal_manager();
	all->toks = NULL;
	all->reds = NULL;
	all->fds[0] = STDIN_FILENO;
	all->fds[1] = STDOUT_FILENO;
	all->i = get_next_line(0, &all->buff);
	crontold(all);
	if ((all->env = ft_tab_to_list(env, 0)) == NULL)
		new_env(all);
	else
	{
		update_shlvl(all);
		update_pwd(all, 1, 1);
	}
	all->ret = new_elem("?=0", 0);
	all->red = 0;
	all->wd_backup = NULL;
	all->wd_backup = getcwd(all->wd_backup, 0);
}

void		init_all(t_all *all, char **env, int ac, char **av)
{
	init_allbis(all, env, ac, av);
	all->bad = NULL;
	all->shouldi = malloc(sizeof(int *) * 1);
	all->dir = ft_split(all->buff, ' ');
	if (checkquote(*all, all->buff) == 1)
	{
		all->xdir = ft_split(all->buff, ' ');
		all->pdir = ft_split(all->buff, ' ');
		if (all->buff[0] != '|')
			write(2, "No Multilines\n", 14);
		return ((void)letsgnl(all));
	}
	all->countsmc = (g_freete == 0) ? pipecount(*all, all->buff, ';') + 1 : 0;
	all->pdir = ft_splitmini(all->buff, ';');
	crocofail(all, all->pdir, ';');
	all->tube = (g_freete == 0 && all->pdir[0] && all->countsmc > 0) ?
				pipecount(*all, all->pdir[0], '|') : 0;
	all->countsmc = (all->tube >= 0) ? all->countsmc : 0;
	all->data = all->countsmc;
	all->xdir = ft_splitmini(all->pdir[0], '|');
	(all->tube > 0 && all->countsmc > 1) ? crocofail(all, all->pdir, '|') : 0;
	all->exec = NULL;
}
