/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/09/29 18:40:42 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		 writenotfound(t_all *all)
{
	if (all->buff[0] == '\0')
	{
		all->ret->value = ft_itoa(0);
		all->countpipe--;
		return ;
	}
	if (all->dir[0])
	{
		write(1, "minishell: ", 11);
		write(1, all->dir[0] , (!all->dir[0]) ? 0 :ft_strlen(all->dir[0]));
		write(1, ": command not found\n", 21);
	}
	all->ret->value = ft_itoa(127);
	all->countpipe--;
}

int			letsgnl(t_all *all)
{
	int ok;

	ok = checkonlyret(all->pdir[0], all);
	get_dir();
	free(all->buff);
	all->i = get_next_line(0, &all->buff);
	all->countpipe = pipecount(*all, all->buff, ';') + 1;
	all->data = all->countpipe;
//	freedir(all->dir);
//	all->dir = NULL;
	freedir(all->pdir);
	all->pdir = NULL;
	all->pdir = (all->countpipe > 1) ?
		ft_splitmini(all->buff, ';') : ft_split(all->buff, '\0');
	return (0);
}

void	init_all(t_all *all, char **env)
{
	all->i = get_next_line(0, &all->buff);
	all->env = ft_tab_to_list(env);
	all->ret = new_elem("?=0");
	all->countpipe = pipecount(*all, all->buff, ';') + 1;
	all->data = all->countpipe;
	all->pdir = (all->countpipe > 1) ?
		ft_splitmini(all->buff, ';') : ft_split(all->buff, '\0');
	all->dir = ft_split(all->buff, ' ');
	all->fd = 0;
	all->fd_backup = 0;
	all->ret->value = ft_itoa(0);
	all->reds = NULL;
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
		printf("received SIGINT\n");
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
		printf(" received SIGQUIT\n");
}

/*void	handle_sigeof(int sig)
{
	write(0, "0", 1);
}*/

int		signal_manager()
{
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit);
	//signal(SIGINT, &handle_sigeof);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_all	all;
	int		i;
	int		index;

	get_dir();
	(void)ac;
	(void)av;
	init_all(&all, env);
	while (check(all.pdir[all.data - all.countpipe], &all) == 1 && all.i > 0)
	{
		signal_manager();
		all.countpipe = checkquote(all.buff) ? 0 : all.countpipe;
		env = ft_list_to_tab(all.env, 0);
		i = counttoken(all);
		index = 0;
		while (index <= i)
		{
			all.pdir[all.data - all.countpipe] =  dolar(all);
			index++;
		}
		if	(all.countpipe > 0 && parse_command(&all, env) == 0 && !io_manager_dup(&all, 0))
			writenotfound(&all);
		if (all.countpipe < 1)
			letsgnl(&all);
	}
	return (freelance(&all));
}
