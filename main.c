/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/14 12:46:00 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// pensez a revoir le parsing du strcmp

int	main(int ac, char **av, char **env)
{
	t_all	all;
//	int		i;
//	char	**dir;
//	char	*buff;

	all.i = 0;
	get_dir();
	(void)ac;
	(void)av;
	all.dir = NULL;
	all.i= get_next_line(0, &all.buff);
	while (check(all.buff) == 1 && all.i> 0)
	{
		all.dir = ft_split(all.buff, ' ');
		if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "cd") == 0)
			cd(all.dir);
		else if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "pwd") == 0)
			pwd(all.buff);
		else if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "echo") == 0)
			echo(all.buff, all.dir);
		else if (ft_strncmp(all.buff, "export ", 7) == 0)
			env = ft_export_core(all.buff + 7, env);
		else if (ft_strncmp(all.buff, "export", 6) == 0)
			env = ft_export_core(NULL, env);
		else if (ft_strncmp(all.buff, "env", 3) == 0)
			ft_putenv(env);
		else if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "test") == 0)
			ft_tab_to_list(env);
		else if (ft_strlen(all.buff) > 0 && ft_strcmp(all.dir[0], "env") == 0)
			ft_putenv(env);
		else
		{
			write(1, "minishell: ", 11);
			write(1, all.buff, ft_strlen(all.buff));
			write(1, ": command not found\n", 21);
		//	system(all.buff);
		}
		get_dir();
		free(all.buff);
		all.i= get_next_line(0, &all.buff);
	}
//	freelance(&*all.dir, all.buff);
	return (0);
}
