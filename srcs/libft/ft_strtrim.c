/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:32:21 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/12 16:34:19 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_char_set(const char *set, char c)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		start;
	int		end;
	char	*new;

	i = 0;
	if (!set || !s1)
		return (NULL);
	while (is_char_set(set, s1[i]) == 1 && s1[i])
		i++;
	start = i;
	while (s1[i])
		i++;
	if (i != start)
		while (is_char_set(set, s1[--i]) == 1)
			;
	end = i;
	if (!(new = malloc(sizeof(char) * (end - start + 2))))
		return (NULL);
	i = 0;
	while (end >= start)
		new[i++] = s1[start++];
	new[i] = '\0';
	return (new);
}

char		*ft_strtrimf(char *s1, const char *set)
{
	int		i;
	int		start;
	int		end;
	char	*new;

	i = 0;
	if (!set || !s1)
		return (NULL);
	while (is_char_set(set, s1[i]) == 1 && s1[i])
		i++;
	start = i;
	while (s1[i])
		i++;
	if (i != start)
		while (is_char_set(set, s1[--i]) == 1)
			;
	end = i;
	if (!(new = malloc(sizeof(char) * (end - start + 2))))
		return (NULL);
	i = 0;
	while (end >= start)
		new[i++] = s1[start++];
	new[i] = '\0';
	free(s1);
	return (new);
}
