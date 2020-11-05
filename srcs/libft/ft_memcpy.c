/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:20:10 by chgilber          #+#    #+#             */
/*   Updated: 2019/10/16 18:27:22 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char		*pst;
	unsigned char	*cpy;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	pst = (const char*)src;
	cpy = (unsigned char*)dst;
	i = 0;
	while (i < n)
	{
		cpy[i] = pst[i];
		i++;
	}
	return (dst);
}
