/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:30:12 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/12 17:38:39 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		end(char *buff, t_all *all)
{
	int		i;
	char	**arg;

	i = 0;
	arg = ft_split(buff, ' ');
	if (arg[1])
	{
		while (arg[1][i] && ft_isdigit(arg[1][i]) == 0)
			i++;
		if (i == ft_strlen(arg[1]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, arg[1], ft_strlen(arg[1]));
			write(2, ": numeric argument required", 28);
			update_return(all, 255);
		}
		else
			update_return(all, ft_atoi(arg[1]));
	}
	free_tab(arg);
	return (0);
}

/* 
** A FAIRE : REMETTRE A LA LIGNE APRES AFFICHAGE ET NE PAS AFFICHER LE REPERTOIRE SUR ANCIENNE LIGNE
** MODE = 0 : NE PAS AFFICHER VAR
** MODE = 1 : AFFICHER VAR
*/

int		ft_put_error(char *error, char *var, int mode)
{
	write(2, "minishell:", 10);
	if (mode == 1)
	{
		ft_putstr_fd(" \'", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("\':", 2);
	}
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
	return (-1);
}
