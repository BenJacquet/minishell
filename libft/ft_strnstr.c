/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:05:09 by chgilber          #+#    #+#             */
/*   Updated: 2019/10/16 16:48:53 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int i;
	unsigned int a;

	i = 0;
	if (!*to_find)
		return ((char*)str);
	while (str[i] != '\0' && i < len)
	{
		a = 0;
		while (str[i + a] == to_find[a] && str[i + a] != '\0' &&
		((i + a) < len))
			a++;
		if (to_find[a] == '\0')
			return ((char*)str + i);
		i++;
	}
	return (NULL);
}
