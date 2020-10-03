/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:38:04 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/03 18:06:21 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** MODE = 1 : REMPLACEMENT DE STDIN/STDOUT PAR LE FD
** MODE = 0 : RESTAURATION DE STDIN/STDOUT
*/

int	io_manager_dup(t_all *all, int mode)
{
/*	int	fds[2];
	if (pipe(fds) != 0)
		return (-1);*/
	if (mode == 1 && all->reds)
	{
		all->reds->fd = open(all->reds->file, all->reds->red, 0777);
		printf("\033[1;31m-----------------\nUSED_RED:\nfile=[%s]\nred=[%d]\nfd=[%d]\n-----------------\n\033[0m", all->reds->file, all->reds->red, all->reds->fd);
		if (all->reds->red == 2)
		{
			all->fd = dup(STDIN_FILENO);
			dup2(all->reds->fd, STDIN_FILENO);
			close(all->reds->fd);

		}
		else if (all->reds->red == 521 || all->reds->red == 1537)
		{
			all->fd = dup(STDOUT_FILENO);
			dup2(all->reds->fd, STDOUT_FILENO);
			close(all->reds->fd);
		}
	}
	else if (mode == 0 && all->reds)
	{
		printf("\033[1;31m-----------------\nUSED_RED:\nfile=[%s]\nred=[%d]\nfd=[%d]\n-----------------\n\033[0m", all->reds->file, all->reds->red, all->reds->fd);
		if (all->reds->red == 2)
		{
			dup2(all->fd, STDIN_FILENO);
			close(all->fd);
		}
		else if (all->reds->red == 521 || all->reds->red == 1537)
		{
			dup2(all->fd, STDOUT_FILENO);
			close(all->fd);
		}
		free_red(all->reds);
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
	printf("\033[1;32m-----------------\nNEW_RED:\nfile=[%s]\nred=[%d]\nfd=[%d]\n-----------------\n\033[0m", new->file, new->red, new->fd);
	return (head);
}

void free_red(t_red *red)
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
			open(current->file, current->red);
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

int which_redirection(t_all *all, int *start)
{
	if (ft_strncmp(all->toks->value + *start, ">>", 2) == 0)
		all->red = (O_CREAT | O_APPEND | O_WRONLY);
	else if (ft_strncmp(all->toks->value + *start, ">", 1) == 0)
		all->red = (O_CREAT | O_TRUNC | O_WRONLY);
	else if (ft_strncmp(all->toks->value + *start, "<", 1) == 0)
		all->red = (O_RDWR);
	if (all->red == 1537 || all->red == 521 || all->red == 2)
		all->toks->end = *start;
//	else if (all->red == 2)
//		all->toks->end = 0;
	if (all->red == 2 || all->red == 1537)
		*start += 1;
	else if (all->red == 521)
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
			printf("inside_name start=[%d]tok->value[%d]=[%c]\n", *start, *start, (*toks)->value[*start]);
			file = ft_dup_until_red((*toks)->value + *start);
			*start += ft_strlen(file);
			break ;
		}
	}
	return (file);
}

int handle_redirections(t_all *all)
{
	int start;
	char *file;
	t_tok	*head;

	head = all->toks;
	start = 0;
	file = NULL;
	all->reds = NULL;
	if (!all->toks)
		return (-1);
	while (all->toks)
	{
		while (all->toks->value && ft_strlen(all->toks->value + start))
		{
			which_redirection(all, &start);
			if (all->red == 0)
				start++;
			else if (all->red)
			{
				printf("before-start=[%d]tok->value[%d]=[%c]\n", start, start, all->toks->value[start]);
				file = get_filename(&all->toks, &start);
				printf("after-start=[%d]tok->value[%d]=[%c]\n", start, start, all->toks->value[start]);
			}
			if (file)
				all->reds = new_red(all->reds, all->red, &file);
			all->red = 0;
		}
		start = 0;
		all->toks = all->toks->next;
	}
	all->reds = process_reds(all->reds);
	all->toks = head;
	//printf("\033[1;31m-----------------\nLAST_RED:\nfilename=[%s]\nred=[%d]\nfd=[%d]\n-----------------\n\033[0m", all->reds->filename, all->reds->red, all->reds->fd);
	return (1);
}