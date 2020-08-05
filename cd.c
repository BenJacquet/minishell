/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:17:15 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/05 12:13:08 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd(char **dir)
{
	int	i;

	i = chdir((dir[1]));
	if (i == -1)
	{
		write(1, "bash: cd: ", 10);
		write(1, dir[1], ft_strlen(dir[1]));
		write(1, ": No such file or directory\n", 28);
	}
	return (i);
}
