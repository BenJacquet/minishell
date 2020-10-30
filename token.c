/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 15:52:23 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/29 18:06:35 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skipsquot(t_all *all, int *j, int *i, int index)
{
	if (all->dir[index][*i] == '\"')
		(*j)++;
	if (all->dir[index][*i] == '\'' && checksquote(all->dir[index]) % 2 == 0
			&& (*j % 2 == 0 && checkdquote(all->dir[index]) % 2 == 0))
	{
		(*i)++;
		while (all->dir[index][*i] != '\'')
			(*i)++;
	}
}

int		counttoken(t_all *all)
{
	int	token;
	int	i;
	int	j;

	token = 0;
	j = 0;
	if (all->dir)
	{
		while (all->dir[j] && ft_strlen(all->dir[j]) > 0)
		{
			i = 0;
			all->j = 0;
			while (all->dir[j][i])
			{
				skipsquot(all, &all->j, &i, j);
				if (all->dir[j][i] == '$')
					token++;
				i++;
			}
			j++;
		}
	}
	return (token);
}

void	finddolar(t_all *all, int *i, int j, char **tmp)
{
	tmp[0] = malloc(sizeof(char) * (*i + 1));
	tmp[0] = ft_strncpy(tmp[0], all->dir[j], *i);
	tmp[1] = malloc(sizeof(char) * ft_strlen(all->dir[j]));
	ft_bzero(tmp[1], ft_strlen(all->dir[j]));
	(*i)++;
	all->j = 0;
	while (*i < ft_strlen(all->dir[j]) && all->dir[j][*i] != ' ')
	{
		if (all->dir[j][*i] == '\'' || all->dir[j][*i] == '\"'
				|| all->dir[j][*i] == '$')
			break ;
		tmp[1][all->j] = all->dir[j][*i];
		(*i)++;
		all->j++;
	}
	tmp[1][all->j] = '\0';
	tmp[2] = NULL;
	tmp[2] = ft_getenv(all, tmp[1], (all->kotey[j] == 2) ? 0 : 1);
	if ((all->j == 0))
		tmp[0] = ft_strjoinf(tmp[0], "$");
	else
		tmp[0] = ft_strjoinf(tmp[0], tmp[2]);
	free(tmp[2]);
}

int		nicedolbro(t_all *all, int i, int j, char **tmp)
{
	finddolar(all, &i, j, tmp);
	all->j = 0;
	while (i <= ft_strlen(all->dir[j]) && all->dir[j][i])
	{
		tmp[1][all->j] = all->dir[j][i];
		i++;
		all->j++;
	}
	tmp[1][all->j] = '\0';
	tmp[0] = ft_strjoin(tmp[0], tmp[1]);
	free(tmp[1]);
	return (i);
}

void	dolar(t_all *all)
{
	int		i;
	int		j;
	char	*tmp[3];

	j = 0;
	while (all->dir[j] && ft_strlen(all->dir[j]) > 0)
	{
		i = 0;
		if (all->kotey[j] == 3)
		{
			if	(ft_tablen(all->dir) < j + 1)
				j++;
			else
				break ;
		}
		all->pipe = (all->kotey[j] == 2) ? 1 : 0;
		while (all->dir[j][i])
		{
			skipsquot(all ,&all->pipe, &i, j);
			if (all->dir[j][i] == '$')
			{
				i = nicedolbro(all, i, j, tmp);
				free(all->dir[j]);
				all->dir[j] = ft_strdup(tmp[0]);
				free(tmp[0]);
				break ;
			}
			i++;
		}
		j++;
	}
}
