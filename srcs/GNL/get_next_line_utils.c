/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:59:14 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/05 16:59:14 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dest, char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
}

char	*ft_strjoinn(char *s1, char *s2, size_t len)
{
	char			*str;
	char			*tmp;
	unsigned int	i;
	unsigned int	j;

	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + len + 1))))
		return (NULL);
	tmp = str;
	i = 0;
	j = 0;
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] && len > 0)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str - (str - tmp));
}

char	*ft_strchr(const char *st, int c)
{
	int		i;

	i = 0;
	while (st[i])
	{
		if (st[i] == c)
			return ((char *)st + i);
		i++;
	}
	if (st[i] == 0 && 0 == c)
		return ((char *)st + i);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if (i < start)
		len = 0;
	if (!(str = (char*)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (i < len && s[start] && s[i])
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
