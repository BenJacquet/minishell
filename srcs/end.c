/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:30:12 by chgilber          #+#    #+#             */
/*   Updated: 2020/11/23 13:46:18 by chgilber         ###   ########.fr       */
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
	else if (arg[2] && arg[1] && ft_isdigit(arg[1][i]) == 1)
		return (end2(all, arg));
	free_tab(arg);
	return (0);
}

int		checkonlyret(char *buff, t_all *all)
{
	int i;

	i = all->i;
	i = 0;
	if (!buff)
		return (1);
	while (buff[i] == ' ')
		i++;
	if (ft_strlen(buff + i) == 4 && ft_strncmp(buff + i, "exit", 4) == 0)
		return (0);
	if (ft_strlen(buff + i) > 4 && ft_strncmp(buff + i, "exit ", 5) == 0)
		return (0);
	else
		return (1);
}

int		check(char *buff, t_all *all)
{
	int i;

	i = 0;
	if (!buff)
		return (1);
	while (buff[i] == ' ')
		i++;
	if (ft_strlen(buff + i) == 4 && ft_strncmp(buff + i, "exit", 4) == 0 &&
		!all->tube)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (ft_strlen(buff + i) > 4 && ft_strncmp(buff + i, "exit ", 5) == 0 &&
		!all->tube)
	{
		write(1, "exit\n", 5);
		return (end(buff, all));
	}
	else
		return (1);
}
