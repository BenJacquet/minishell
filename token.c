/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 15:52:23 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/28 20:05:19 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skipsquot(int *j, int *i, char *dir)
{
	if (dir[*i] == '\"')
		(*j)++;
	if (dir[*i] == '\'' && checksquote(dir) % 2 == 0
			&& (*j % 2 == 0 && checkdquote(dir) % 2 == 0))
	{
		(*i)++;
		while (dir[*i] != '\'')
			(*i)++;
	}
}

int		counttoken(t_all *all, char **dir)
{
	int	token;
	int	i;
	int	j;

	token = 0;
	j = 0;
	if (dir)
	{
		while (dir[j] && ft_strlen(dir[j]) > 0)
		{
			i = 0;
			all->j = 0;
			while (dir[j][i])
			{
				skipsquot(&all->j, &i, dir[j]);
				if (dir[j][i] == '$')
					token++;
				i++;
			}
			j++;
		}
	}
	return (token);
}

char	*finddolar(t_all *all, int *i, int j, char **tmp, char **dir)
{
	char	*dol;

	dol = NULL;
	tmp[0] = malloc(sizeof(char) * (*i + 1));
	tmp[0] = ft_strncpy(tmp[0], dir[j], *i);
	tmp[1] = malloc(sizeof(char) * ft_strlen(dir[j]));
	ft_bzero(tmp[1], ft_strlen(dir[j]));
	(*i)++;
	all->j = 0;
	while (*i < ft_strlen(dir[j]) && dir[j][*i] != ' ')
	{
		if (dir[j][*i] == '\'' || dir[j][*i] == '\"'
				|| dir[j][*i] == '$')
			break ;
		tmp[1][all->j] = dir[j][*i];
		(*i)++;
		all->j++;
	}
	tmp[1][all->j] = '\0';
	tmp[2] = ft_getenv(all, tmp[1], (all->kotey[j] == 2) ? 0 : 1);
	dol = (all->j == 0) ? ft_strjoin(dol, "$") : ft_strjoin(tmp[0], tmp[2]);
	return (dol);
}

int		nicedolbro(t_all *all, int i, int j, char **tmp, char **dir)
{
	tmp[3] = finddolar(all, &i, j, tmp, dir);
	free(tmp[0]);
	free(tmp[2]);
	all->j = 0;
	while (i <= ft_strlen(dir[j]) && dir[j][i])
	{
		tmp[1][all->j] = dir[j][i];
		i++;
		all->j++;
	}
	tmp[1][all->j] = '\0';
	tmp[3] = ft_strjoin(tmp[3], tmp[1]);
	free(tmp[1]);
	return (i);
}

void	dolar(t_all *all, char **dir)
{
	int		i;
	int		j;
	char	*tmp[4];

	tmp[3] = NULL;
	j = 0;
	printf("dir[%d] = [%s]\n" , j, dir[j]);
	while (dir[j] && ft_strlen(dir[j]) > 0)
	{
		i = 0;
		printf("dir[%d] = [%s]\n" , j, dir[j]);
		all->pipe = (all->kotey[j] == 2) ? 1 : 0;
		printf("dir[%d] = [%s]\n" , j, dir[j]);
		while (dir[j][i])
		{
			skipsquot(&all->pipe, &i, dir[j]);
			if (dir[j][i] == '$')
			{
				i = nicedolbro(all, i, j, &*tmp, dir);
				free(dir[j]);
				dir[j] = ft_strdup(tmp[3]);
				printf("afterdir[%d][%d] = [%s]\n" , j, i, dir[j]);
				free(tmp[3]);
				break ;
			}
			i++;
		}
		j++;
	}
}
