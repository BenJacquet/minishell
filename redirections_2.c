/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:01:06 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/25 15:48:51 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	*new_red(t_red *head, int red, char **file)
{
	t_red	*new;
	t_red	*current;

	current = head;
	if (!(new = malloc(sizeof(t_red))))
		return (NULL);
	new->red = red;
	new->fd = 0;
	new->file = ft_strdup(*file);
	new->last = 0;
	new->next = NULL;
	if (!head)
		head = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	free(*file);
	*file = NULL;
	return (head);
}

void	free_red(t_red *red)
{
	if (red)
	{
		if (red->file != NULL)
			free(red->file);
		red->file = NULL;
		red->red = 0;
		red->next = NULL;
		free(red);
		red = NULL;
	}
}

void	get_last(t_all *all, t_red *reds)
{
	t_red	*last_in;
	t_red	*last_out;

	last_in = NULL;
	last_out = NULL;
	while (reds != NULL)
	{
		if (reds->red == 2)
			last_in = reds;
		else
			last_out = reds;
		reds = reds->next;
	}
	if (last_in)
	{
		all->fds[0] = open(last_in->file, last_in->red, 0666);
		last_in->last = 1;
	}
	if (last_out)
	{
		all->fds[1] = open(last_out->file, last_out->red, 0666);
		last_out->last = 1;
	}
}

/*void	check_reds(t_all *all)
{
	t_red	*current;

	current = all->reds;
	if (all->reds)
	{
		while (all->reds)
		{
			current = all->reds;
			all->reds = all->reds->next;
			if (current->red != 2 && current->last == 0)
			{
				current->fd = open(current->file, current->red, mask);
				close(current->fd);
			}
			free_red(current);
		}
	}
	all->reds = NULL;
}*/

void	process_reds(t_all *all, int mask)
{
	t_red	*current;

	(void)mask;
	current = all->reds;
	if (all->reds)
	{
		get_last(all, all->reds);
		while (all->reds)
		{
			current = all->reds;
			all->reds = all->reds->next;
			if (current->red != 2 && current->last == 0)
			{
				current->fd = open(current->file, current->red, 0666);
				close(current->fd);
			}
			free_red(current);
		}
	}
	all->reds = NULL;
}

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
