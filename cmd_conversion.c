/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:30:56 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/12 15:30:35 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*new_token(char *token, t_tok *previous)
{
	t_tok	*new;

	if (!(new = malloc(sizeof(t_tok))))
		return (NULL);
	new->value = ft_strdup(token);
	new->beg = 0;
	new->end = ft_strlen(token);
	if (!ft_strncmp(token, ">", 1) || !ft_strncmp (token, "<", 1))
		new->ignore = 1;
	else
		new->ignore = 0;
	new->previous = previous;
	new->next = NULL;
	return (new);
}

char	*clean_token(t_tok *tok)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(char) * (tok->end - tok->beg) + 1)))
		return (NULL);
	while (tok->beg + i < tok->end)
	{
		new[i] = tok->value[tok->beg + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**convert_tokens_tab(t_tok *lst)
{
	int i;
	char **tab;
	t_tok *current;

	i = 0;
	current = lst;
	tab = NULL;
	while (current != NULL)
	{
		if (current->ignore == 0)
			i++;
		current = current->next;
	}
	if (!(tab = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	current = lst;
	i = 0;
	while (current != NULL)
	{
		if (current->ignore == 0 && current->beg < current->end)
			tab[i++] = clean_token(current);
		current = current->next;
	}
	tab[i] = NULL;
	current = lst;
/*	for (;current != NULL; current = current->next)
		printf("\033[1;31m(%p)\033[0m\nvalue=[%s]\nrange[%d-%d]\nignore=[%d]\nprevious=[%p]\nnext=[%p]\n", current,current->value,current->beg,current->end,current->ignore,current->previous,current->next);
	printf("new->dir---------\n");
	for (int j=0;tab[j];j++)
		printf("\033[1;33mtab[j]=[%s]\n\033[0m",tab[j]);*/
	free_tokens(lst);
	return (tab);
}

t_tok	*convert_tokens_lst(char **cmd)
{
	int i;
	t_tok *head;
	t_tok *current;
	t_tok *previous;

	i = 0;
	head = NULL;
	current = NULL;
	previous = NULL;
/*	printf("old->dir---------\n");
	for (int j=0;cmd[j];j++)
		printf("\033[1;33mtab[j]=[%s]\n\033[0m",cmd[j]);*/
	if (cmd)
	{
		current = new_token(cmd[i++], NULL);
		head = current;
		while (cmd[i] != NULL)
		{
			current->next = new_token(cmd[i++], current);
			current = current->next;
		}
	}
	free_tab(cmd);
	current = head;
	return (head);
}
