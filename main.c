/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/09/04 13:52:44 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pensez a revoir le parsing du strcmp
//
int			 writenotfound(t_all all)
{
	write(1, "minishell: ", 11);
	write(1, all.pdir[all.data - all.countpipe], 
			ft_strlen(all.pdir[all.data - all.countpipe]));
	write(1, ": command not found\n", 21);
	all.countpipe--;
	return (all.countpipe);
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

/*int main(int ac, char **av, char **env)
{
	int i = 0;
	char **new = tab_dup(env);
	t_env *new_list = ft_tab_to_list(new);
	t_env *backup = new_list;
    printf("------------------------------------------------------------\n");
	for (i = 0 ;new_list != NULL; new_list = new_list->next, i++)
	{
		printf("new_list(%p)->name=%s\n", new_list, new_list->name);
		printf("new_list(%p)->value=%s\n", new_list, new_list->value);
	}
	printf("new_list_len=%d\n", i);
	new_list = backup;
	free_tab(new);
	new = ft_list_to_tab(new_list);
	new = ft_export_core("test=123", new);
    printf("------------------------------------------------------------\n");
    for (i = 0; new[i]; i++)
        printf("new env[%d]=%s\n", i, new[i]);
	printf("new_len=%d\n", ft_tablen(new));
	new = ft_unset_core("test", new);
	printf("-------------------TEST PUTENV(new)------------------\n");
	ft_putenv(new);
	printf("-------------------TEST EXPORT(NULL)------------------\n");
	new = ft_export_core(NULL, new);
	free_tab(new);
}*/


int	main(int ac, char **av, char **env)
{
	t_all	all;
	int		i;
	int		index;

	all.i = 0;
	get_dir();
	(void)ac;
	(void)av;
	all.dir = NULL;
	all.i = get_next_line(0, &all.buff);
	all.env = ft_tab_to_list(env);
	all.countpipe = pipecount(all, all.buff, ';') + 1;
	all.data = all.countpipe;
	all.pdir = (all.countpipe > 1) ?
		ft_splitmini(all.buff, ';') : ft_split(all.buff, '\0');
	while (check(all.buff) == 1 && all.i > 0)
	{
		i = counttoken(all);
		index = 0;
		while (index <= i)
		{
			all.pdir[all.data - all.countpipe] =  dolar(all);
			index++;
		}
		all.dir = ft_split(all.pdir[all.data - all.countpipe], ' ');
		//		printf("dir {%s} et pdri{%s}, all.countpipe = %d\n", all.dir[1], all.pdir[all.data - all.countpipe], all.countpipe);
		
		if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "cd") == 0)
		{
			cd(all.dir, all);
			all.countpipe--;
		}
		else if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "pwd") == 0)
		{
			pwd(all.buff);
			all.countpipe--;
		}
		else if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "echo") == 0)
		{
			echo(all);
			all.countpipe--;
		}
		else if (ft_strncmp(all.buff, "export ", 7) == 0)
		{
			env = ft_export_core(all.buff + 7, env);
			all.countpipe--;
		}
		else if (ft_strncmp(all.buff, "export", 6) == 0)
		{
			env = ft_export_core(NULL, env);
			all.countpipe--;
		}
		else if (ft_strncmp(all.buff, "unset", 5) == 0)
		{
			env = ft_unset_core(all.buff + 6, env);
			all.countpipe--;
		}
		else if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "env") == 0)
		{
			ft_putenv(env);
			all.countpipe--;
		}
		else if ((all.exec = get_path(&all, env)) != NULL)
		{
			printf("exec=%s\n", all.exec);
			run_exec(all.exec, all.dir, env);
			all.countpipe--;
		}
		else
			all.countpipe = writenotfound(all);
		if (all.countpipe < 1)
			letsgnl(&all);
	}
	//	freelance(&*all.dir, all.buff);
	return (0);
}