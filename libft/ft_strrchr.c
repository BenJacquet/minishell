/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:01:29 by chgilber          #+#    #+#             */
/*   Updated: 2019/10/16 19:41:30 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	oc;
	char	*st;
	int		i;
	char	*a;

	if (!s)
		return (NULL);
	i = 0;
	a = (0);
	oc = (char)c;
	st = (char*)s;
	while (st[i])
	{
		if (st[i] == oc)
			a = (st + i);
		i++;
	}
	if (a)
		return (a);
	if (st[i] == 0 && 0 == oc)
		return (st + i);
	return (NULL);
}
