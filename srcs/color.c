/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 16:12:46 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/18 16:13:04 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		ft_color(t_all *all)
{
	if (ft_tablen(all->dir) == 1)
		write(1, "red green yellow blue magenta cyan or white needed\n", 52);
	else if (ft_tablen(all->dir) == 2)
	{
		if (!ft_strcmp(all->dir[1], "red"))
			write(1, "\x1B[31m", 6);
		else if (!ft_strcmp(all->dir[1], "green"))
			write(1, "\x1B[32m", 6);
		else if (!ft_strcmp(all->dir[1], "yellow"))
			write(1, "\x1B[33m", 6);
		else if (!ft_strcmp(all->dir[1], "blue"))
			write(1, "\x1B[34m", 6);
		else if (!ft_strcmp(all->dir[1], "magenta"))
			write(1, "\x1B[35m", 6);
		else if (!ft_strcmp(all->dir[1], "cyan"))
			write(1, "\x1B[36m", 6);
		else if (!ft_strcmp(all->dir[1], "white"))
			write(1, "\x1B[37m", 6);
		else
			return (ft_put_error("invalid argument", all->dir[0], 0, 1));
	}
	else
		return (ft_put_error("too many arguments", all->dir[0], 0, 1));
	return (0);
}
