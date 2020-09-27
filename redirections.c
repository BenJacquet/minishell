/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:38:04 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/27 18:47:50 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red		*new_red(t_red *head, int red, char *filename)
{
	t_red *new;
	t_red *current;

	new = NULL;
	current = head;
	if (!(new = malloc(sizeof(t_red))))
		return (NULL);
	new->red = red;
	new->fd = 0;
	new->filename = filename;
	new->next = NULL;
	if (!head)
		head = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	printf("\033[1;32m-----------------\nNEW_RED:\nfilename=[%s]\nred=[%d]\nfd=[%d]\n-----------------\n\033[0m", new->filename, new->red, new->fd);
	return (head);
}

void free_red(t_red *red)
{
	if (red)
	{
		if (red->filename != NULL)
			free(red->filename);
		free(red);
	}
}

t_red *process_reds(t_red *reds)
{
	t_red *current;

	current = reds;
	if (reds)
	{
		while (reds->next != NULL)
		{
			current = reds;
			reds = reds->next;
			open(current->filename, current->red);
			close(current->fd);
			free_red(current);
		}
	}
	return (reds);
}

int ft_isinset(const char *set, char c)
{
	int i;

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

char *ft_dup_until_red(char *src)
{
	int i;
	char *dup;

	i = 0;
	dup = NULL;
	if (src[i])
	{
		while (src[i])
		{
			if (ft_isinset("<>", src[i]) == 1)
				break;
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
	}
	return (dup);
}

char *get_filename(char **token, int *i, int *start)
{
	char *filename;

	filename = NULL;
	while (filename == NULL)
	{
		if (token[*i] == NULL)
			break ;
		if (token[*i][*start] == '\0')
		{
			(*i)++;
			*start = 0;
		}
		if (token[*i][*start] != '\0')
		{
			filename = ft_dup_until_red(token[*i] + *start);
			*start += ft_strlen(filename);
			break ;
		}
	}
	return (filename);
}

int handle_redirections(t_all *all)
{
	int i;
	int start;
	char *filename;

	i = 0;
	start = 0;
	filename = NULL;
	if (!all->dir)
		return (-1);
	while (all->dir[i])
	{
		start = 0;
		while (all->dir[i][start] != '\0')
		{
			start += which_redirection(all, all->dir[i] + start);
			if (all->red == 0)
				start++;
			filename = get_filename(all->dir, &i, &start);
			all->reds = new_red(all->reds, all->red, filename);
		}
		i++;
	}
	all->reds = process_reds(all->reds);
	printf("\033[1;31m-----------------\nLAST_RED:\nfilename=[%s]\nred=[%d]\nfd=[%d]\n-----------------\n\033[0m", all->reds->filename, all->reds->red, all->reds->fd);
	return (1);
}