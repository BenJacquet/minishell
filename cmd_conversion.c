/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:30:56 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/13 17:24:17 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	*new_token(char *token, t_tok *previous, int whole)
{
	t_tok	*new;

	if (!(new = malloc(sizeof(t_tok))))
		return (NULL);
	new->value = ft_strdup(token);
	new->beg = 0;
	new->end = ft_strlen(token);
	new->whole = whole;
	if (!ft_strncmp(token, ">", 1) || !ft_strncmp(token, "<", 1))
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

int		ft_tokslen(t_tok *toks)
{
	int		len;

	len = 0;
	while (toks != NULL)
	{
		if (toks->ignore == 0)
			len++;
		toks = toks->next;
	}
	return (len);
}

char	**convert_tokens_tab(t_tok *lst)
{
	int		i;
	char	**tab;
	t_tok	*current;

	current = lst;
	i = ft_tokslen(lst);
	if (!(tab = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (current != NULL)
	{
		if (current->ignore == 0 && current->beg < current->end)
			tab[i++] = clean_token(current);
		current = current->next;
	}
	tab[i] = NULL;
	current = lst;
	free_tokens(lst);
	return (tab);
}

t_tok	*convert_tokens_lst(char **cmd, int *whole)
{
	int		i;
	t_tok	*head;
	t_tok	*current;
	t_tok	*previous;

	i = 0;
	head = NULL;
	current = NULL;
	previous = NULL;
	if (cmd)
	{
		current = new_token(cmd[i], NULL, whole[i]);
		head = current;
		i++;
		while (cmd[i] != NULL)
		{
			current->next = new_token(cmd[i], current, whole[i]);
			current = current->next;
			i++;
		}
	}
	free_tab(cmd);
	current = head;
	return (head);
}
