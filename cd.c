/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:17:15 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/28 18:39:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd(char **dir, t_all *all)
{
	int		i;

	i = 0;
	update_pwd(all, 1, 0);
	if (dir[1])
	{
		i = chdir((dir[1]));
		if (i == -1)
		{
			write(1, "minishell: cd: ", 15);
			write(1, dir[1], ft_strlen(dir[1]));
			write(1, ": No such file or directory\n", 28);
			return (1);
		}
	}
	else
		i = chdir(ft_getenv(all, "HOME", 1));
	update_pwd(all, 0, 0);
	if (i == -1)
		write(1, "minishell: cd: HOME not set\n", 29);
	return (0);
}
