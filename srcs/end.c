/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:30:12 by chgilber          #+#    #+#             */
/*   Updated: 2020/11/09 15:06:33 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		end2(t_all *all, char **arg)
{
	free_tab(arg);
	write(2, "minishell: exit: too many arguments\n", 36);
	all->countsmc = 0;
	return (1);
}

int		numskip(char **arg, int i)
{
	char	*max;
	int		index;
	int		sign;

	index = 0;
	sign = 0;
	max = "9223372036854775807\0";
	while ((arg[1][i] && ft_isdigit(arg[1][i]) == 1) ||
		((arg[1][0] == '+' || arg[1][0] == '-') && i == 0))
		i++;
	if (i >= 19)
	{
		if (i == 20)
			sign = (arg[1][0] == '-' || arg[1][0] == '+') ? 1 : 0;
		if ((i - sign) == 19)
		{
			while (index < 19 && max[index] - arg[1][index + sign] == 0)
				index++;
			i = ((max[index] - arg[1][index]) >= 0) ? i : 0;
			return (i);
		}
		return (0);
	}
	return (i);
}

int		end(char *buff, t_all *all)
{
	int		i;
	char	**arg;

	i = 0;
	arg = ft_split(buff, ' ');
	if (arg[2] && arg[1] && ft_isdigit(arg[1][i]) == 1)
		return (end2(all, arg));
	if (arg[1])
	{
		i = numskip(arg, i);
		if (i != ft_strlen(arg[1]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, arg[1], ft_strlen(arg[1]));
			write(2, ": numeric argument required\n", 29);
			update_return(all, 2);
		}
		else
			update_return(all, ft_atoi(arg[1]));
	}
	free_tab(arg);
	return (0);
}

int		ft_put_error(char *error, char *var, int env, int mode)
{
	if (env == 0)
		write(2, "minishell:", 10);
	else
		write(2, "env:", 4);
	if (mode == 1)
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(var, 2);
		ft_putstr_fd(":", 1);
	}
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
	return (-1);
}
