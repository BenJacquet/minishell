/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 13:59:43 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/09 14:02:38 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, const char *src, int dstsize)
{
	int	a;
	int	i;

	a = 0;
	i = 0;
	if (!dest || !src)
		return (NULL);
	if (dstsize > 0)
	{
		while (a < dstsize && src[a])
		{
			dest[a] = src[a];
			a++;
		}
		dest[a] = '\0';
	}
	return (dest);
}
