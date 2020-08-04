/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/04 18:35:34 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check(char	*buff)
{
	//	printf("%d,%s\n", ft_strlen(buff), buff);
	if (ft_strlen(buff) == 4 && ft_strncmp(buff, "exit", 4) == 0)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (ft_strlen(buff) > 4 && ft_strncmp(buff, "exit ", 5) == 0)
	{
		write(1, "exit\n", 5);
		return (end(buff));
	}
	else
		return (1);
}
int		main(int ac, char **av)
{
	int		i;
	char	**dir;
	char	*buff;

	i = 0;
	get_dir();
	get_next_line(0, &buff);
	while(check(buff) == 1)
	{
		dir = ft_split(buff, ' ');
		if(ft_strncmp(dir[0], "cd", 2) == 0)
			cd(dir);
		else
			system(buff);
		get_dir();
		free(buff);
		get_next_line(0,&buff);
	}
	free(buff);
	return (0);
}
