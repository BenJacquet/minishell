/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 13:59:43 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/07 18:36:27 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, int dstsize)
{
	int	a;

	a = 0;
	if (!dest || !src)
		return (NULL);
	if (dstsize > 0)
	{
		while (a < dstsize && src[a])
		{
			dest[a] = src[a];
			a++;
		}
	}
	dest[a] = '\0';
	return (dest);
}
