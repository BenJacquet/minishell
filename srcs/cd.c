/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:17:15 by chgilber          #+#    #+#             */
/*   Updated: 2020/11/17 17:49:05 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		cd(char **dir, t_all *all)
{
	int		i;
	char	*home;

	i = 0;
	update_pwd(all, 1, 0);
	if (dir[1])
	{
		i = chdir((dir[1]));
		if (i == -1)
		{
			write(2, "minishell: cd: ", 15);
			write(2, dir[1], ft_strlen(dir[1]));
			write(2, ": No such file or directory\n", 28);
			return (1);
		}
	}
	else
	{
		home = ft_getenv(all, "HOME", 1);
		i = chdir(home);
		free(home);
	}
	update_pwd(all, 0, 0);
	if (i == -1)
		write(2, "minishell: cd: HOME not set\n", 29);
	return (0);
}
