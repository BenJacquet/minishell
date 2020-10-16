/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/16 18:01:40 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		writenotfound(t_all *all)
{
	if (all->buff[0] == '\0')
	{
		update_return(all, 0);
		all->countpipe--;
		return ;
	}
	if (all->dir[0])
	{
		write(1, "minishell: ", 11);
		write(1, all->dir[0], (!all->dir[0]) ? 0 : ft_strlen(all->dir[0]));
		write(1, ": command not found\n", 21);
	}
	update_return(all, 127);
	all->countpipe--;
}

int			letsgnl(t_all *all)
{
	g_freete = 0;
	get_dir();
	free(all->buff);
	signal_manager(all);
	all->i = get_next_line(0, &all->buff);
	signal_manager(all);
//	printf("countpipe = [%d]\n", all->countpipe);
	crontold(all);
	if (checkquote(all->buff) == 1)
		write(1, "No Multilines\n", 14);
	g_builtin = 0;
//	write(1, "-", 1);
//	write(1, all->buff, ft_strlen(all->buff));
//	write(1, "-", 1);
//	all->countpipe = (g_freete == 0) ? pipecount(*all, all->buff, ';') + 1 : 0 ;
	all->countpipe = pipecount(*all, all->buff, ';') + 1;
	freedir(all->pdir);
	all->pdir = ft_splitmini(all->buff, ';');
	all->tube = (all->pdir[0] && all->countpipe > 0) ?
		pipecount(*all, all->pdir[0], '|') : 0;
	all->countpipe = (all->tube >= 0) ? all->countpipe : 0;
	all->data = all->countpipe;
	freedir(all->xdir);
	all->xdir = ft_splitmini(all->pdir[0], '|');
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
		if (all->dol[all->igno - 1] > 0)
			printf("dol[%d]=%d , all.pdir[j][dol[igno]] = [%c]\n", all->igno - 1, all->dol[all->igno - 1], all->pdir[all->data - all->countpipe][all->dol[all->igno - 1]]); // penser a ne pas check les - 666
		index++;
	}
	return (1);
}
int			pipeornotpipe(t_all *all, char **env)
{
	int here;

	here = all->data - all->countpipe;
	all->tube = (g_freete == 0 && all->pdir[here] && all->countpipe > 0) ?
				pipecount(*all, all->pdir[here], '|') : 0;
	if (all->tube > 0)
		multidir(all);
	else if (all->countpipe > 0)
	{
		all->countpipe = checkquote(all->buff) ? 0 : all->countpipe;
		tokentranslate(all);
		if (all->countpipe > 0 && parse_command(all, env) == 0)
			writenotfound(all);
		g_builtin = 0;
	}
	io_manager_dup_out(all);
	env = update_env(all, env);
	return (0);
}

int			main(int ac, char **av, char **env)
{
	t_all	all;

	init_all(&all, env, ac, av);
	while (check(all.pdir[all.data - all.countpipe], &all) == 1 && all.i > 0)
	{
		printf("data = %d , count = %d , tube = %d, [%s]\n", all.data, all.countpipe, all.tube, all.pdir[all.data - all.countpipe]);
		//		printf("xdir[0] = [%s] et xdir[1] = [%s] et tube = %d\n", all.xdir[0], all.xdir[1], all.tube);
		signal_manager(&all);
		g_freete = 0;
		pipeornotpipe(&all, env);
		//	if (g_freete == 1)
		//		letsgnl(&all);
		if (all.countpipe < 1)
			letsgnl(&all);
	}
	return (freelance(&all, env));
}
