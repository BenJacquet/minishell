/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 15:52:23 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/14 12:47:32 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dolar(char *buff, char **env)
{
	int		i;
	char	*dol;
	char	*tmp;

	i = 0;
	while (buff[i] != ' ')
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	i = 0;
	while (buff[i] != ' ')
	{
		tmp[i] = buff[i];
		i++;
	}
	dol = ft_getenv(tmp, env);
	free(tmp);
	return (dol);
}
