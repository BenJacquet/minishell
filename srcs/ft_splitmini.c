/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 16:29:10 by chgilber          #+#    #+#             */
/*   Updated: 2020/10/28 19:27:08 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int		in_charset(char c, char *charset)
{
	if (charset[0] == c)
		return (1);
	return (0);
}

int				quote(char *s, int i)
{
	if (s[i] == '\'' && checksquote(s) % 2 == 0)
	{
		i++;
		while (s[i] != '\'' && s[i])
			i++;
		if (s[i] != '\0')
			i++;
	}
	else if (s[i] == '\"' && checkdquote(s) % 2 == 0)
	{
		i++;
		while (s[i] != '\"' && s[i])
			i++;
		if (s[i] != '\0')
			i++;
	}
	else
		i++;
	return (i);
}

int				ft_count_word(char *s, char *charset)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (in_charset(s[i], charset))
		{
			words++;
			if (in_charset(s[i], charset))
				while (in_charset(s[i], charset) && s[i] != '\0')
					i++;
		}
		i = quote(s, i);
	}
	return (words);
}

static char		*ft_len_word(char *s, char *charset)
{
	int		len;
	int		k;
	char	*word;

	len = 0;
	while (s[len] && !in_charset(s[len], charset))
			len = quote(s, len);
	if (!(word = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	k = 0;
	while (len > k)
	{
		word[k] = s[k];
		k++;
	}
	word[len] = '\0';
	return (word);
}

char			**ft_splitmini(char *s, char c)
{
	int		i;
	int		k;
	char	**tab;
	char	charset[1];

	charset[0] = c;
	if (!s || !(tab = malloc(sizeof(char *) * (ft_count_word(s, charset) + 2))))
		return (NULL);
	k = 0;
	i = 0;
	while (s[i])
	{
		if (in_charset(s[i], charset))
			while (s[i] != '\0' && in_charset(s[i], charset))
				i++;
		else
		{
			tab[k++] = ft_len_word(s + i, charset);
			i = i + ft_strlen(tab[k - 1]);
		}
	}
	tab[k] = NULL;
	return (tab);
}
