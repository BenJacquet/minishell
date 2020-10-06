/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 15:52:23 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/06 17:53:33 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skipsquot(t_all all, int *j, int *i)
{
	int	index;

	index = all.data - all.countpipe;
	if (all.pdir[index][*i] == '\"')
		(*j)++;
	if (all.pdir[index][*i] == '\'' && checksquote(all.pdir[index]) % 2 == 0 &&
		(*j % 2 == 0 && checkdquote(all.pdir[index]) % 2 == 0))
	{
		(*i)++;
		while (all.pdir[index][*i] != '\'')
			(*i)++;
	}
}

int		counttoken(t_all all)
{
	int	token;
	int	i;
	int	j;

	token = 0;
	all.j = 0;
	j = all.data - all.countpipe;
	i = 0;
	if (all.pdir)
	{
		if (all.pdir[j] && ft_strlen(all.pdir[j]) > 0)
		{
			while (all.pdir[j][i])
			{
				skipsquot(all, &all.j, &i);
				if (all.pdir[j][i] == '$')
					token++;
				i++;
			}
		}
	}
	return (token);
}

char	*finddolar(t_all all, int *i, int j, char **tmp)
{
	char	*dol;

	dol = NULL;
	tmp[0] = malloc(sizeof(char) * (*i + 1));
	tmp[0] = ft_strncpy(tmp[0], all.pdir[j], *i);
	tmp[1] = malloc(sizeof(char) * ft_strlen(all.pdir[j]));
	ft_bzero(tmp[1], ft_strlen(all.pdir[j]));
	(*i)++;
	all.j = 0;
	while (*i < ft_strlen(all.pdir[j]) && all.pdir[j][*i] != ' ')
	{
		if (all.pdir[j][*i] == '\'' || all.pdir[j][*i] == '\"'
				|| all.pdir[j][*i] == '$')
			break ;
		tmp[1][all.j] = all.pdir[j][*i];
		(*i)++;
		all.j++;
	}
	tmp[1][all.j] = '\0';
	tmp[2] = ft_getenv(&all, tmp[1], (j % 2 == 1) ? 1 : 0);
	dol = (all.j == 0) ? ft_strjoin(tmp[0], "$") : ft_strjoin(tmp[0], tmp[2]);
	free(tmp[0]);
	free(tmp[2]);
	return (dol);
}

int		nicedolbro(t_all all, int i, int j, char **tmp)
{
	tmp[3] = finddolar(all, &i, j, tmp);
	all.j = 0;
	while (i <= ft_strlen(all.pdir[j]) && all.pdir[j][i])
	{
		tmp[1][all.j] = all.pdir[j][i];
		i++;
		all.j++;
	}
	tmp[1][all.j] = '\0';
	tmp[3] = ft_strjoin(tmp[3], tmp[1]);
	free(tmp[1]);
	return (i);
}

char	*dolar(t_all all)
{
	int		i;
	int		j;
	char	*tmp[4];

	tmp[3] = NULL;
	j = all.data - all.countpipe;
	i = 0;
	all.pipe = 0;
	if (all.pdir[j] && ft_strlen(all.pdir[j]) > 0)
	{
		while (all.pdir[j][i])
		{
			skipsquot(all, &all.pipe, &i);
			if (all.pdir[j][i] == '$')
			{
				i = nicedolbro(all, i, j, &*tmp);
				return (tmp[3]);
			}
			i++;
		}
	}
	return (all.pdir[j]);
}
