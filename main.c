/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/17 12:35:23 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

// pensez a revoir le parsing du strcmp
int	main(int ac, char **av, char **env)
{
	t_all	all;

	all.i = 0;
	get_dir();
	(void)ac;
	(void)av;
	all.dir = NULL;
	all.i = get_next_line(0, &all.buff);
	all.env = ft_tab_to_list(env);
	all.dir = ft_splitmini(all.buff, ';');
	all.countpipe = pipecount(all, ';') + 1;
	all.data = all.countpipe;
	all.pdir = (all.countpipe > 1) ?
		ft_splitmini(all.buff, ';') : ft_split(all.buff, '\0');
	while (check(all.buff) == 1 && all.i > 0)
	{
		all.dir = (all.countpipe > 0) ?
			ft_split(all.pdir[all.data - all.countpipe], ' ') : ft_split(all.buff, ' ');
				//printf("dir {%s} et pdri{%s}, all.countpipe = %d\n", all.dir[1], all.pdir[all.data - all.countpipe], all.countpipe);
		if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "cd") == 0)
		{
			cd(all.dir);
			all.countpipe--;
		}
		else if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "pwd") == 0)
		{
			pwd(all.buff);
			all.countpipe--;
		}
		/*else if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "echo") == 0)
		{
			echo(all.pdir[all.data - all.countpipe], all.dir);
			all.countpipe--;
		}*/
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
		else if (ft_strncmp(all.buff, "env", 3) == 0)
		{
			ft_putenv(env);
			all.countpipe--;
		}
		else if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "env") == 0)
		{
			ft_putenv(env);
			all.countpipe--;
		}
		else if ((all.exec = get_path(&all)) != NULL)
		{
			printf("exec=%s\n", all.exec);
			run_exec(all.exec, all.dir, env);
			all.countpipe--;
		}
		else
		{
			write(1, "minishell: ", 11);
			write(1, all.buff, ft_strlen(all.buff));
			write(1, ": command not found\n", 21);
			all.countpipe--;
			//	system(all.buff);
		}
		if (all.countpipe < 1)
		{
			get_dir();
			free(all.buff);
			all.i = get_next_line(0, &all.buff);
			all.countpipe = pipecount(all, ';') + 1;
			all.data = all.countpipe;
			//		freedir(all.pdir);
			//		freedir(all.dir);
			all.pdir = (all.countpipe > 1) ?
				ft_splitmini(all.buff, ';') : ft_split(all.buff, '\0');
		}
		//	else
		//		freedir(all.dir);
	}
	//	freelance(&*all.dir, all.buff);
	return (0);
}
