/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:38:04 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/12 16:26:49 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_fds(t_all *all)
{
	all->fds[0] = STDIN_FILENO;
	all->fds_backup[0] = STDIN_FILENO;
	all->fds[1] = STDOUT_FILENO;
	all->fds_backup[1] = STDOUT_FILENO;
}

int		no_command(t_all *all, int mode)
{
	//printf ("before all->fds[0]=[%d]\nall->fds[1]=[%d]\n", all->fds[0], all->fds[1]);
	if (mode == 1)
	{
		if (all->fds[0] != 0)
			close(all->fds[0]);
		if (all->fds[1] != 1)
			close(all->fds[1]);
	}
	//printf ("after all->fds[0]=[%d]\nall->fds[1]=[%d]\n", all->fds[0], all->fds[1]);
	return (0);
}

/*
** MODE = 1 : REMPLACEMENT DE STDIN/STDOUT PAR LE FD
** MODE = 0 : RESTAURATION DE STDIN/STDOUT
*/

int	io_manager_dup(t_all *all, int mode)
{
/*	int	fds[2];
	if (pipe(fds) != 0)
		return (-1);*/
	if (!all->dir[0])
		return (no_command(all, mode));
	if (mode == 1)
	{
		if (all->fds[0] != 0)
		{
			all->fds_backup[0] = dup(STDIN_FILENO);
			dup2(all->fds[0], STDIN_FILENO);
			close(all->fds[0]);
		}
		if (all->fds[1] != 1)
		{
			all->fds_backup[1] = dup(STDOUT_FILENO);
			dup2(all->fds[1], STDOUT_FILENO);
			close(all->fds[1]);
		}
	}
	else if (mode == 0)
	{
		if (all->fds[0] != 0)
		{
			dup2(all->fds_backup[0], STDIN_FILENO);
			close(all->fds_backup[0]);
		}
		if (all->fds[1] != 1)
		{
			dup2(all->fds_backup[1], STDOUT_FILENO);
			close(all->fds_backup[1]);
		}
		reset_fds(all);
	}
	return (0);
}

t_red		*new_red(t_red *head, int red, char **file)
{
	t_red *new;
	t_red *current;

	new = NULL;
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
	//printf("\033[1;32m-----------------\nNEW_RED:\nfile=[%s]\nred=[%d]\nfd=[%d]\n-----------------\n\033[0m", new->file, new->red, new->fd);
	return (head);
}

void free_red(t_red *red)
{
	if (red)
	{
		//printf("\033[1;31m-----------------\nFREED_RED:\nfile=[%s]\nred=[%d]\n-----------------\n\033[0m", red->file, red->red);
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
		all->fds[0] = open(last_in->file, last_in->red, all->mask);
		last_in->last = 1;
		//printf("last_in->value=[%s]\nall->fds[0]=[%d]\n", last_in->file, all->fds[0]);
	}
	if (last_out)
	{
		all->fds[1] = open(last_out->file, last_out->red, all->mask);
		last_out->last = 1;
		//printf("last_out->value=[%s]\nall->fds[1]=[%d]\n", last_out->file, all->fds[1]);
	}
}

void	process_reds(t_all *all, int mask)
{
	t_red *current;

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
				current->fd = open(current->file, current->red, mask);
				close(current->fd);
			}
			printf("\033[1;32m-----------------\nPROCESSED_RED:\nfile=[%s]\nred=[%d]\nlast_in=[%d]\n-----------------\n\033[0m", current->file, current->red, current->last);
			free_red(current);
		}
	}
	all->reds = NULL;
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

int which_redirection(t_all *all, int *start)
{
	if (ft_strncmp(all->toks->value + *start, ">>", 2) == 0)
		all->red = (O_CREAT | O_APPEND | O_RDWR);
	else if (ft_strncmp(all->toks->value + *start, ">", 1) == 0)
		all->red = (O_CREAT | O_TRUNC | O_RDWR);
	else if (ft_strncmp(all->toks->value + *start, "<", 1) == 0)
		all->red = (O_RDWR);
	if (all->red == 1538 || all->red == 522 || all->red == 2)
	{
		//printf("start=[%d]\n", *start);
		all->toks->end = (all->toks->end == ft_strlen(all->toks->value) ? *start : all->toks->end);
		//printf("all->toks->end=[%d]\n", all->toks->end);
		if (all->toks->next && all->toks->value[(*start + 1)] == '\0')
		{
			all->toks = all->toks->next;
			all->toks->ignore = 1;
			all->toks = all->toks->previous;
		}
	}
	if (all->red == 2 || all->red == 1538)
		*start += 1;
	else if (all->red == 522)
		*start += 2;
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

char *get_filename(t_tok **toks, int *start)
{
	char *file;

	file = NULL;
	while (file == NULL)
	{
		if (toks == NULL || (*toks)->value == NULL)
			break ;
		if ((*toks)->value[*start] == '\0' && (*toks)->next != NULL)
		{
			(*toks) = (*toks)->next;
			*start = 0;
		}
		if ((*toks)->value[*start] != '\0')
		{
			//printf("before_start=[%d]\n", *start);
			file = ft_dup_until_red((*toks)->value + *start);
			*start += ft_strlen(file);
			//printf("file=[%s]\nafter_start=[%d]\n", file, *start);
			/*if (file)
				(toks*)->beg = */
			//(*toks)->beg = (*toks)->end;
			//printf("inside_name start=[%d]tok->value[%d]=[%c]\n", *start, *start, (*toks)->value[*start]);
			break ;
		}
	}
	return (file);
}

void	get_redirections(t_all *all)
{
	int		start;
	char	*file;

	start = 0;
	file = NULL;
	while (all->toks)
	{
		while (all->toks->value && ft_strlen(all->toks->value + start))
		{
			which_redirection(all, &start);
			if (all->red == 0)
				start++;
			else if (all->red)
			{
				//printf("before-start=[%d]tok->value[%d]=[%c]\n", start, start, all->toks->value[start]);
				file = get_filename(&all->toks, &start);
				//printf("after-start=[%d]tok->value[%d]=[%c]\n", start, start, all->toks->value[start]);
			}
			if (file)
				all->reds = new_red(all->reds, all->red, &file);
			all->red = 0;
		}
		start = 0;
		all->toks = all->toks->next;
	}
}

int handle_redirections(t_all *all)
{
	t_tok	*head;

	head = all->toks;
	all->reds = NULL;
	if (!all->toks)
		return (-1);
	get_redirections(all);
	process_reds(all, all->mask);
	all->toks = head;
	//printf("\033[1;31m-----------------\nLAST_RED:\nfilename=[%s]\nred=[%d]\nfd=[%d]\n-----------------\n\033[0m", all->reds->filename, all->reds->red, all->reds->fd);
	return (1);
}
