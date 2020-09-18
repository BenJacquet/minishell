/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/09/18 15:34:23 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pensez a revoir le parsing du strcmp
//
void		 writenotfound(t_all *all)
{
	if (all->buff[0] == '\0')
	{
	//	free(all->ret->value);
		all->ret->value = ft_itoa(0);
		all->countpipe--;
		return ;
	}
	write(1, "minishell: ", 11);
//	write(1, all->pdir[all->data - all->countpipe],
//		ft_strlen(all->pdir[all->data - all->countpipe]));
	write(1, all->dir[0] , ft_strlen(all->dir[0]));
	write(1, ": command not found\n", 21);
//	free(all->ret->value);
	all->ret->value = ft_itoa(127);
	all->countpipe--;
}

int			letsgnl(t_all *all)
{
	get_dir();
	free(all->buff);
	all->i = get_next_line(0, &all->buff);
	all->countpipe = pipecount(*all, all->buff, ';') + 1;
	all->data = all->countpipe;
	//		freedir(all->pdir);
	//		freedir(all->dir);
	all->pdir = (all->countpipe > 1) ?
		ft_splitmini(all->buff, ';') : ft_split(all->buff, '\0');
	return (0);
}

int		builtins_others(t_all *all)
{
	int pipe_bkp;

	pipe_bkp = all->countpipe;
	if (ft_strlen(all->buff) > 0 && ft_strcmp(all->dir[0], "cd") == 0)
	{
		all->ret->value = ft_itoa(cd(all->dir, *all));
		all->countpipe--;
	}
	else if (ft_strlen(all->buff) > 0 && ft_strcmp(all->dir[0], "pwd") == 0)
	{
		all->ret->value = ft_itoa(pwd(all->buff));
		all->countpipe--;
	}
	else if (ft_strlen(all->buff) > 0 && ft_strcmp(all->dir[0], "echo") == 0)
	{
		all->ret->value = ft_itoa(echo(*all));
		all->countpipe--;
	}
	return (all->countpipe != pipe_bkp ? 1 : 0);
}

int		builtins_env(t_all *all)
{
	int pipe_bkp;

	pipe_bkp = all->countpipe;
	if (ft_strncmp(all->buff, "export", 6) == 0)
	{
		ft_export_core(all, all->buff + 6);
		all->countpipe--;
	}
	else if (ft_strncmp(all->buff, "unset", 5) == 0)
	{
		ft_unset_core(all, all->buff + 6);
		all->countpipe--;
	}
	else if (ft_strlen(all->buff) > 0 && ft_strcmp(all->dir[0], "env") == 0)
	{
		ft_putenv(all->env);
		all->countpipe--;
	}
	return (all->countpipe != pipe_bkp ? 1 : 0);
}

int	parse_command(t_all *all, char **env)
{
//	for (int i = 0; all->dir[i]; i++)
//		printf("all->dir[%d]=%s\n--------------------------------\n", i, all->dir[i]);

//		printf("all->pdir[%d]=%s\n--------------------------------\n", i, all->pdir[i]);
	joinquote(all);
//	for (int i = 0; all->dir[i]; i++)
//		printf("all->dir[%d]=%s\n--------------------------------\n", i, all->dir[i]);
if (!(all->pdir[all->data - all->countpipe]))
	{
		all->countpipe--;
		return (1);
	}
	if ((ft_strlen(all->pdir[all->data - all->countpipe]) > 0 &&
		((ft_strcmp(all->dir[0], "cd") == 0) ||
		ft_strcmp(all->dir[0], "pwd") == 0 ||
		ft_strcmp(all->dir[0], "echo") == 0)))
	{
		builtins_others(all);
		return (1);
	}
	else if ((ft_strlen(all->pdir[all->data - all->countpipe]) > 0 &&
			((ft_strcmp(all->dir[0], "env") == 0) ||
			ft_strncmp(all->pdir[all->data - all->countpipe], "unset", 5) == 0 ||
			ft_strncmp(all->pdir[all->data - all->countpipe], "export", 6) == 0)))
	{
		builtins_env(all);
		return (1);
	}
	else if ((all->exec = get_path(all, env)) != NULL)
	{
		run_exec(all, all->exec, all->dir, env);
		all->countpipe--;
		return (1);
	}
	return (0);
}

void	init_all(t_all *all, char **env)
{
	all->i = 0;
	all->dir = NULL;
	all->i = get_next_line(0, &all->buff);
	all->env = ft_tab_to_list(env);
	all->ret = new_elem("?=0");
	all->countpipe = pipecount(*all, all->buff, ';') + 1;
	all->data = all->countpipe;
	all->pdir = (all->countpipe > 1) ?
		ft_splitmini(all->buff, ';') : ft_split(all->buff, '\0');
	all->fd = 0;
	all->fd_backup = 0;
	all->ret->value = ft_itoa(0);
	all->red = (O_CREAT | O_TRUNC | O_RDWR);	// '>'
	//all->red = (O_CREAT | O_APPEND | O_RDWR);	// '>>'
	//all->red = (O_RDWR);						// '<'
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
	while (check(all.buff) == 1 && all.i > 0)
	{
		//signal_manager();
		env = ft_list_to_tab(all.env, 0);
		i = counttoken(all);
		index = 0;
		while (index <= i)
		{
			all.pdir[all.data - all.countpipe] =  dolar(all);
			index++;
		}
		all.dir = ft_split(all.pdir[all.data - all.countpipe], ' ');
		//		printf("dir {%s} et pdri{%s}, all.countpipe = %d\n", all.dir[1], all.pdir[all.data - all.countpipe], all.countpipe);
		if	(all.countpipe > 0 && parse_command(&all, env) == 0)
			writenotfound(&all);
		if (all.countpipe < 1)
			letsgnl(&all);
	}
	//	freelance(&*all.dir, all.buff);
	return (0); //check(all.buff)); // retourner l'exit et free
}
