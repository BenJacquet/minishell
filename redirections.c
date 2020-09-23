/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:38:04 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/23 17:12:07 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int which_redirection(t_all *all, char *token)
{
	if (ft_strncmp(token, ">>", 2) == 0)
	{
		all->red = (O_CREAT | O_APPEND | O_RDWR);
		return (2);
	}
	else if (ft_strncmp(token, ">", 1) == 0)
	{
		all->red = (O_CREAT | O_TRUNC | O_RDWR);
		return (1);
	}
	else if (ft_strncmp(token, "<", 1) == 0)
	{
		all->red = (O_RDWR);
		return (1);
	}
	else
		all->red = 0;
	return (0);
}

char		*ft_dup_until_red(char *src)
{
	int		i;
	char	*dup;

	i = 0;
	while (src[i])
	{
		if (src[i] == '<' || src[i] == '>')
			break ;
		i++;
	}
	dup = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (src[i] == '<' && src[i] == '>')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int		sticky_redirections(t_all *all, int *i, int *start)
{
	char	*filename;
	int j = 0;
	*start = 0;
	printf("all->dir[%d] + %d=[%s]\n", *i, *start, all->dir[*i] + *start);
	while (all->dir[*i] + *start &&
			*start = which_redirection(all, all->dir[*i] + *start) != 0 && j != 5)
	{
		filename = ft_dup_until_red(all->dir[*i] + *start);
		printf("filename=[%s]\n", filename);
		open(filename, all->red);
		*start += ft_strlen(filename);
		free(filename);
		j++;
	}
	return (0);
}

int handle_files(t_all *all)
{
	int i;
	int start;

	i = 0;
	start = 0;
	if (!all->dir)
		return (-1);
	while (all->dir[i])
	{
		printf("all->dir[%d]=[%s]\n", i, all->dir[i]);
		if ((start = which_redirection(all, all->dir[i])) != 0)
		{
			if (all->dir[i] + start)
				sticky_redirections(all, &i, &start);
			if (all->dir[i])
				open(all->dir[i++], all->red);
		}
		else
			i++;
	}
	return (0);
}
