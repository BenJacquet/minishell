/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:01:06 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/05 22:17:10 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/*
** MODE = 1 : check si le fichier existe
** MODE = 0 : check si le fichier est un dossier
*/

int		check_red(t_all *all, t_red *red, int mode)
{
	struct stat	status;
	int			ret;

	ret = 0;
	ret = stat(red->file, &status);
	if (mode == 0)
		return (ret);
	if (mode == 1 && (S_ISDIR(status.st_mode) || slash(red->file, 0) ||
		all->bad || (red->red == I_R && ret == -1)))
	{
		if (!all->bad)
		{
			if (!(all->bad = malloc(sizeof(t_red))))
				return (1);
			all->bad->red = red->red;
			all->bad->bad = 1;
			all->bad->file = ft_strdup(red->file);
			all->bad->last = 0;
			all->bad->exists = red->exists;
			all->bad->next = NULL;
		}
		return (1);
	}
	return (0);
}

t_red	*new_red(t_all *all, t_red *head, int red, char *file)
{
	t_red	*new;
	t_red	*current;

	current = head;
	if (!(new = malloc(sizeof(t_red))))
		return (NULL);
	new->red = red;
	new->file = ft_strdup(file);
	new->last = 0;
	new->exists = (check_red(all, new, 0) == -1 ? 0 : 1);
	new->bad = check_red(all, new, 1);
	new->next = NULL;
	if (!head)
		head = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	return (head);
}

t_red	*free_red(t_red *red)
{
	if (red)
	{
		if (red->file)
			free(red->file);
		red->red = 0;
		red->next = NULL;
		free(red);
	}
	return (NULL);
}

void	get_last(t_all *all, t_red *reds)
{
	t_red	*last_in;
	t_red	*last_out;

	last_in = NULL;
	last_out = NULL;
	while (reds)
	{
		if (reds->red == I_R)
			last_in = reds;
		else
			last_out = reds;
		if (reds->bad)
			break ;
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

void	process_reds(t_all *all)
{
	t_red	*current;

	current = all->reds;
	if (all->reds)
	{
		get_last(all, all->reds);
		while (all->reds)
		{
			current = all->reds;
			all->reds = all->reds->next;
			if (current->red != I_R && current->last == 0 && !current->bad)
				close(open(current->file, current->red, 0666));
			current = free_red(current);
		}
	}
	all->reds = NULL;
}
