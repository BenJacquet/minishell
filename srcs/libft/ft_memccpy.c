/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:13:58 by chgilber          #+#    #+#             */
/*   Updated: 2019/10/16 18:55:21 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const char		*s;
	unsigned char	*d;
	unsigned char	id;
	size_t			i;

	s = (const char*)src;
	d = (unsigned char*)dst;
	id = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		if (id == d[i])
			return ((void*)(dst + i + 1));
		i++;
	}
	return (0);
}
