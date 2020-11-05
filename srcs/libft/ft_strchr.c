/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:15:10 by chgilber          #+#    #+#             */
/*   Updated: 2019/10/16 19:38:39 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	oc;
	char	*st;
	int		i;

	i = 0;
	oc = (char)c;
	st = (char*)s;
	if (!s)
		return (NULL);
	while (st[i])
	{
		if (st[i] == oc)
			return (st + i);
		i++;
	}
	if (st[i] == 0 && 0 == oc)
		return (st + i);
	return (NULL);
}
