/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:56:52 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/08 13:18:27 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	i;

	a = 0;
	i = 0;
	if (!dest || !src)
		return (0);
	while (src[i])
		i++;
	if (dstsize > 0)
	{
		while (a < dstsize && src[a])
		{
			dest[a] = src[a];
			a++;
		}
		dest[a] = '\0';
	}
	return (i);
}
