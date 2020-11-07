/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:15:00 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/06 16:58:52 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		ft_varlen(char *var, int mode)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (var[i] != '\0' && var[i] != '=' && var[i] != '+')
		i++;
	if (mode == 0)
		return (i);
	while (var[i + j] != '\0')
		j++;
	return (j);
}

int		ft_isinset(const char *set, char c)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

/*
**	MODE 0 : Si le dernier char est un '/'
**	MODE 1 : Si la string contient un '/'
*/

int		slash(char *str, int mode)
{
	int		i;

	i = (mode == 0 ? ft_strlen(str) : 0);
	if (i > 0 && mode == 0)
	{
		if (str[i - 1] == '/' || str[i - 1] == '.')
			return (1);
	}
	else if (mode == 1)
	{
		while (str[i])
		{
			if (str[i] == '/')
				return (1);
			i++;
		}
	}
	return (0);
}

t_tok	*skip_empty(t_tok *lst)
{
	while (lst && ft_strlen(lst->value) == 0)
		lst = lst->next;
	return (lst);
}