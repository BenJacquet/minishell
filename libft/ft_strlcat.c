/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:01:47 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/18 16:41:27 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ftrlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		o;

	o = 0;
	i = 0;
	while (dest[i] && i < dstsize)
		i++;
	while (src[o] && o + i + 1 < dstsize)
	{
		dest[i + o] = src[o];
		o++;
	}
	if (i != dstsize)
		dest[i + o] = '\0';
	return (i + ftrlen((char*)src));
}
