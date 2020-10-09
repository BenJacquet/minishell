/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/09 18:45:57 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		writenotfound(t_all *all)
{
	all->builtin = 0;
	if (all->buff[0] == '\0')
	{
		all->ret->value = ft_itoa(0);
		all->countpipe--;
		return ;
	}
	if (all->dir[0])
	{
		write(1, "minishell: ", 11);
		write(1, all->dir[0], (!all->dir[0]) ? 0 : ft_strlen(all->dir[0]));
		write(1, ": command not found\n", 21);
	}
	all->ret->value = ft_itoa(127);
	all->countpipe--;
}

int			letsgnl(t_all *all)
{
	int		ok;

	builtin = 0;
	ok = checkonlyret(all->pdir[0], all);
	get_dir();
	free(all->buff);
	all->i = get_next_line(0, &all->buff);
	crontold(all);
	all->countpipe = pipecount(*all, all->buff, ';') + 1; // peut etre all sans *
	all->data = all->countpipe;
	//	freedir(all->dir);
	//	all->dir = NULL;
	freedir(all->pdir);
	all->pdir = NULL;
	all->pdir = (all->countpipe > 1) ?
		ft_splitmini(all->buff, ';') : ft_split(all->buff, '\0');
	all->builtin = 0;
	return (0);
}

/* 
** 
** 
** 
*/

int			tokentranslate(t_all *all)
{
	int		i;
	int		index;

	i = counttoken(*all);
	index = 0;
	while (index <= i)
	{
		all->pdir[all->data - all->countpipe] = dolar(*all);
		index++;
	}
	return (1);
}

int			main(int ac, char **av, char **env)
{
	t_all	all;

	init_all(&all, env, ac, av);
	while (check(all.pdir[all.data - all.countpipe], &all) == 1 && all.i > 0)
	{
		signal_manager();
		all.countpipe = checkquote(all.buff) ? 0 : all.countpipe;
		env = ft_list_to_tab(all.env, 0);
		tokentranslate(&all);
		if (all.countpipe > 0 && parse_command(&all, env) == 0)
			writenotfound(&all);
		/*if (all.pdir[all.data - all.countpipe] &&
			ft_strlen(all.pdir[all.data - all.countpipe]) > 0)*/
		io_manager_dup(&all, 0);
		if (all.countpipe < 1)
			letsgnl(&all);
	}
	return (freelance(&all));
}
