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

#include "../incs/minishell.h"

void	finddolar(t_all *all, int *i, char **tmp)
{
	tmp[1] = malloc(sizeof(char) * ft_strlen(tmp[0]));
	ft_bzero(tmp[1], ft_strlen(tmp[0]));
	(*i)++;
	all->j = 0;
	while (*i < ft_strlen(tmp[0]) && tmp[0][*i] != ' ')
	{
		if (tmp[0][*i] == '\'' || tmp[0][*i] == '\"'
				|| tmp[0][*i] == '$' || tmp[0][*i] == ';' || tmp[0][*i] == '|')
			break ;
		tmp[1][all->j] = tmp[0][*i];
		(*i)++;
		all->j++;
	}
	tmp[1][all->j] = '\0';
	tmp[2] = ft_getenv(all, tmp[1], (all->kotey == 2) ? 0 : 1);
	if (all->j == 0 && ((tmp[0][1] && (tmp[0][1] == ' ' || tmp[0][1] == '\'' ||
						tmp[0][1] == '\"') && all->mode == 1)
				|| (!tmp[0][1] && all->mode == 0)))
	{
		free(tmp[2]);
		tmp[2] = ft_strdup("$");
	}
	all->diff = ft_strlen(tmp[2]);
}

int		nicedolbro(t_all *all, int i, char **tmp)
{
	finddolar(all, &i, tmp);
	all->j = 0;
	while (i <= ft_strlen(tmp[0]) && tmp[0][i])
	{
		tmp[1][all->j] = tmp[0][i];
		i++;
		all->j++;
	}
	tmp[1][all->j] = '\0';
	tmp[0] = ft_strjoin(tmp[2], tmp[1]);
	free(tmp[2]);
	free(tmp[1]);
	return (i);
}

void	dolar(t_all *all, char *buff, int u)
{
	int		i;
	char	*tmp[4];

	i = 0;
	all->diff = 0;
//	printf("pdirinit =[%s]\n", all->pdir[all->data - all->countsmc] + all->u);
	tmp[3] = malloc(sizeof(char) * (u + all->u + 1));
	tmp[3] = ft_strncpy(tmp[3], all->pdir[all->data - all->countsmc],
	(all->u + u - 1));
	tmp[0] = buff;
//	printf("buff = %s\n", tmp[0]);
//	printf("buff before dolar = %s\n", tmp[3]);
	all->pipe = (all->kotey == 2) ? 1 : 0;
	nicedolbro(all, i, tmp);
	free(all->pdir[all->data - all->countsmc]);
	all->pdir[all->data - all->countsmc] = ft_strjoin(tmp[3], tmp[0]);
//	printf("buff final = %s\n", all->pdir[all->data - all->countsmc]);
	free(tmp[3]);
	free(tmp[0]);
}

char	*tokla(t_all *all, char *buff, int *end, int i)
{
	while (buff[i] && i < *end)
	{
		if (buff[i] == '\"')
			break ;
		all->mode = (all->kotey > 1) ? 1 : 0;
		all->diff = 0;
		if (buff[i] == '$' && all->kotey != 3)
		{
			dolar(all, buff + i, i);
			buff = all->pdir[all->data - all->countsmc] + all->u - 1;
			i = (all->diff < 1) ? i - 1 : i;
			*end = *end + all->diff;
			i = (all->kotey > 1) ? 1 : 0;
		}
		i++;
	}
	*end = i;
	all->kotey = 0;
	return (buff);
}
