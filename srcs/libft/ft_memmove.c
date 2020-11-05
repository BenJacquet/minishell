/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 12:27:52 by chgilber          #+#    #+#             */
/*   Updated: 2019/10/16 18:27:36 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	tmp[len];
	unsigned char	*s;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	s = (unsigned char*)src;
	d = (unsigned char*)dst;
	i = 0;
	while (len > i)
	{
		tmp[i] = s[i];
		i++;
	}
	i = 0;
	while (len > i)
	{
		d[i] = tmp[i];
		i++;
	}
	return (dst);
}
