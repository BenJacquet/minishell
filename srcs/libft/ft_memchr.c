/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:30:41 by chgilber          #+#    #+#             */
/*   Updated: 2019/10/11 20:14:39 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	oc;
	size_t			i;

	str = (unsigned char*)s;
	oc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == oc)
			return ((void*)(s + i));
		i++;
	}
	return (NULL);
}
