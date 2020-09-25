/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:38:04 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/25 17:00:57 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isinset(const char *set, char c)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

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
		return (0);
}

char		*ft_dup_until_red(char *src)
{
	int		i;
	char	*dup;

	i = 0;
	while (src[i])
	{
		if (ft_isinset("<>", src[i]) == 1)
			break ;
		i++;
	}
	dup = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (src[i] && src[i] != '<' && src[i] != '>')
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
	*start = 0;
	while (all->dir[*i][*start] &&
			(*start += (which_redirection(all, all->dir[*i] + *start) != 0)))
	{
		filename = ft_dup_until_red(all->dir[*i] + *start);
		//printf("filename=[%s]\n", filename);
		all->fd = open(filename, all->red);
		//printf("sticky : all->fd=[%d]\n", all->fd);
		*start += ft_strlen(filename);
		//printf("start=[%d]\n", *start);
		if (ft_strlen(filename) == 0 || all->dir[*i][*start + 1] == '\0')
		{
			free(filename);
			break ;
		}
		free(filename);
		if (all->dir[*i][*start] != '\0')
			close(all->fd);
	}
	//printf("\033[0;31msticky redirs inside: all->dir[%d][%d]=[%c]\n\033[0m", *i, *start, all->dir[*i][*start]);
	//if (all->dir[*i][*start] == '\0' && all->red)
	return (0);
}

int handle_redirections(t_all *all)
{
	int i;
	int start;

	i = 0;
	start = 0;
	if (!all->dir)
		return (-1);
	while (all->dir[i])
	{
		//printf("\033[0;33mbefore check : all->dir[%d]=[%s]\n\033[0m", i, all->dir[i]);
		if ((start = which_redirection(all, all->dir[i])) != 0)
		{
			//printf("found redir : all->dir[%d] + %d =[%s]\n", i, start, all->dir[i] + start);
			if (all->dir[i][start] != '\0')
			{
				//printf("sticky redirs : all->dir[%d][%d]=[%c]\n", i, start, all->dir[i][start]);
				//printf("all->dir[i][start]=%d\n", all->dir[i][start]);
				sticky_redirections(all, &i, &start);
			}
			if ((all->dir[i][start] == '\0' && all->dir[i + 1]) ||
				(all->dir[i + 1] && ft_isinset("<>", all->dir[i][start])))
			{
				//printf("one redir : all->dir[%d] + [%d]=[%s]\n", i, start, all->dir[i] + start);
				//printf("one redir : all->dir[%d + 1]=[%s]\n", i, all->dir[i]);
				all->fd = open(all->dir[i + 1], all->red);
			}
			if (all->dir[i + 1] != 0)
				close(all->fd);
		}
		i++;
	}
	//printf("all->red=%d\nall->fd=[%d]\n", all->red, all->fd);
	return (1);
}
