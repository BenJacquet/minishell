/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/06 19:03:54 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	int i;
	char **dir;
	char *buff;

	i = 0;
	get_dir();
	(void)ac;
	(void)av;
	i = get_next_line(0, &buff);
	while (check(buff) == 1 && i > 0)
	{
		dir = ft_split(buff, ' ');
		if (ft_strlen(buff) > 0 && ft_strncmp(dir[0], "cd", 2) == 0)
			cd(dir);
		else if (ft_strncmp(buff, "export ", 7) == 0)
			ft_export(buff + 7, env);
		else if (ft_strncmp(buff, "export", 6) == 0)
			ft_export(NULL, env);
		else if (ft_strncmp(dir[0], "test", 4) == 0)
			ft_tab_to_list(env);
		else if (ft_strncmp(dir[0], "env", 3) == 0)
			ft_putenv(env);
		else
			system(buff);
		get_dir();
		free(buff);
		i = get_next_line(0, &buff);
	}
	freelance(dir, buff);
	return (0);
}
