/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/26 18:47:51 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		writenotfound(t_all *all)
{
	if (all->buff[0] == '\0')
	{
		update_return(all, 0);
		all->countsmc--;
		return ;
	}
	if (all->dir[0])
	{
		write(2, "minishell: ", 11);
		write(2, all->dir[0], (!all->dir[0]) ? 0 : ft_strlen(all->dir[0]));
		write(2, ": command not found\n", 21);
	}
	update_return(all, 127);
	all->countsmc--;
}

int			letsgnl(t_all *all)
{
	g_freete = 0;
	get_dir();
	free(all->buff);
	signal_manager(all);
	all->i = get_next_line(0, &all->buff);
	signal_manager(all);
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

int			tokentranslate(t_all *all)
{
	int		i;
	int		index;

	i = counttoken(all);
	all->dol = malloc(sizeof(int) * (i + 1));
	all->igno = 0;
	index = 0;
	while (index < i)
		all->dol[index++] = -1;
	all->dol[index] = -666;
	index = 0;
	while (index < i)
	{
		dolar(all);
		index++;
	}
	return (1);
}

int			gestionpipe(t_all *all, char ***env)
{
	int fd[all->tube][2];

	free_tab(all->xdir);
	all->countsmc = checkquote(all->buff) ? 0 : all->countsmc;
	tokentranslate(all);
	all->xdir = ft_splitmini(all->pdir[all->data - all->countsmc], '|');
	if (all->tube)
		open_pipes(all, fd);
	if (all->tube > 0)
		multidir(all, env, fd);
	else
	{
		action(all, env, fd);
		*env = update_env(all, *env);
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
		signal_manager(&all);
		g_freete = 0;
		here = all.data - all.countsmc;
		all.tube = (g_freete == 0 && all.pdir[here] && all.countsmc > 0) ?
			pipecount(all, all.pdir[here], '|') : 0;
		gestionpipe(&all, &env);
		if (all.countsmc < 1)
			letsgnl(&all);
	}
	return (freelance(&all, env));
}
