/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/05 16:54:34 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		 writenotfound(t_all *all)
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
	all->builtin = 0;
	return (0);
}

void	init_all(t_all *all, char **env)
{
//	getfcked = 0;
	all->toks = NULL;
    all->reds = NULL;
    all->fds[0] = STDIN_FILENO;
    all->fds[1] = STDOUT_FILENO;
    all->mask = (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	all->i = get_next_line(0, &all->buff);
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

void		handle(int sig) // CTRL D
{
	if (sig == SIGINT)
	{
		printf("c");
	//	getfcked = 1;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
	write(0, "\b\b  \b\b", 2);
	write(1, "Quit: 3", 7);
//	get_dir();
	//	printf(" received SIGQUIT\n");
	}
}


void	handle_sigeof(int sig) // CTRL C
{

	write(0, "\n", 1);
	get_dir();
}

int		signal_manager(t_all *all)
{
	(signal(SIGINT, &handle));
//	if (all->builtin == 2)
	(signal(SIGQUIT, &handle));
//	get_dir();
//	signal(SIGINT, &handle_sigeof);
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
		signal_manager(&all);
		if (getfcked == 1)
			return (freelance(&all));
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
