/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/28 20:00:03 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			letsgnl(t_all *all)
{
	g_freete = 0;
	get_dir(all);
	free(all->buff);
	signal_manager();
	all->i = get_next_line(0, &all->buff);
	signal_manager();
	crontold(all);
	if (checkquote(all->buff) == 1)
		write(1, "No Multilines\n", 14);
	g_builtin = 0;
	all->countsmc = pipecount(*all, all->buff, ';') + 1;
	freedir(all->pdir);
	all->pdir = ft_splitmini(all->buff, ';');
	crocofail(all, all->pdir, ';');
	all->tube = (all->pdir[0] && all->countsmc > 0) ?
		pipecount(*all, all->pdir[0], '|') : 0;
	all->countsmc = (all->tube >= 0) ? all->countsmc : 0;
	all->data = all->countsmc;
	freedir(all->xdir);
	all->xdir = ft_splitmini(all->pdir[0], '|');
	(all->tube > 0 && all->countsmc > 1) ? crocofail(all, all->pdir, '|') : 0;
	return (0);
}

int			gestionpipe(t_all *all)
{
	int fd[all->tube][2];

	free_tab(all->xdir);
	all->countsmc = checkquote(all->buff) ? 0 : all->countsmc;
	all->xdir = ft_splitmini(all->pdir[all->data - all->countsmc], '|');
	if (all->tube)
		open_pipes(all, fd);
	if (all->tube > 0)
		multidir(all, fd);
	else
	{
		action(all, fd);
		all->bad = free_red(all->bad);
		all->countsmc--;
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	t_all	all;
	int		here;

	init_all(&all, env, ac, av);
	while (check(all.pdir[all.data - all.countsmc], &all) == 1 && all.i > 0)
	{
		signal_manager();
		g_freete = 0;
		here = all.data - all.countsmc;
		all.tube = (g_freete == 0 && all.pdir[here] && all.countsmc > 0) ?
			pipecount(all, all.pdir[here], '|') : 0;
		gestionpipe(&all);
		if (all.countsmc < 1)
			letsgnl(&all);
	}
	return (freelance(&all));
}
