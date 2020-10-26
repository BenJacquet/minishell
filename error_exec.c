/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:11:16 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/26 16:13:13 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_exec(t_all *all)
{
	printf("all->countsmc=[%d]\n", all->countsmc);
	if (ft_strcmp(all->dir[0], ".") == 0)
	{
		ft_put_error(
			"filename argument required\n.: usage: .filename [arguments]",
			all->dir[0], 1);
		return (-1);
	}
	else if (ft_strcmp(all->dir[0], "./") == 0)
	{
		ft_put_error("is a directory", all->dir[0], 1);
		return (-1);
	}
	return (0);
}