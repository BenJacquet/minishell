/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:31:34 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/12 17:55:04 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** MODE = 0 : NAME
** MODE = 1 : VALUE
*/
int ft_varlen(char *var, int mode)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (var[i] != '\0' && var[i] != '=' && var[i] != '+')
		i++;
	if (mode == 0)
		return (i);
	while (var[i + j] != '\0')
		j++;
	return (j);
}

int ft_envsize(t_env *lst)
{
	int i;

	if (!lst)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int get_op(char *var)
{
	if (*var == '\0')
		return (0);
	else if (*var == '=')
		return (1);
	else if (ft_strncmp(var, "+=", 2) == 0)
		return (2);
	return (-1);
}

t_env *elem_dup(t_env *elem)
{
	t_env *new;

	if (!(new = malloc(sizeof(t_env))))
		return (NULL);
	new->next = NULL;
	if (elem)
	{
		new->name = ft_strdup(elem->name);
		new->op = elem->op;
		new->value = ft_strdup(elem->value);
	}
	return (new);
}

t_env *new_elem(char *var)
{
	int i;
	int j;
	t_env *elem;

	i = 0;
	j = 0;
	if (!(elem = malloc(sizeof(t_env) + 1)) ||
		!(elem->name = malloc(sizeof(char) * ft_varlen(var, 0) + 1)))
		return (NULL);
	while (var[i] != '\0' && var[i] != '=' && var[i] != '+')
	{
		elem->name[i] = var[i];
		i++;
	}
	elem->name[i] = '\0';
	i += (elem->op = get_op(var + i));
	if (!(elem->value = malloc(sizeof(char) * ft_varlen(var, 1) + 1)))
		return (NULL);
	while (var[i] != '\0')
		elem->value[j++] = var[i++];
	elem->value[j] = '\0';
	elem->next = NULL;
	return (elem);
}

t_env *ft_tab_to_list(char **tab, int erase)
{
	int i;
	t_env *head;
	t_env *current;

	i = 0;
	head = NULL;
	current = NULL;
	if (tab)
	{
		current = new_elem(tab[i++]);
		head = current;
		while (tab[i] != NULL)
		{
			current->next = new_elem(tab[i++]);
			current = current->next;
		}
	}
	if (erase == 1)
		free_tab(tab);
	return (head);
}

char *ft_data_to_string(t_env *elem, int mode)
{
	char *new;
	int len;
	int i;
	int j;

	i = 0;
	j = 0;
	len = ft_strlen(elem->name) + ft_strlen(elem->value) + 1;
	if (!(new = calloc(sizeof(char), len + 1 + 2)))
		return (NULL);
	while (elem->name[j] != '\0')
		new[i++] = elem->name[j++];
	new[i++] = (elem->op != 0 ? '=' : '\0');
	j = 0;
	if (mode == 1 && elem->op != 0)
		new[i++] = '\"';
	while (elem->value[j] != '\0')
		new[i++] = elem->value[j++];
	if (mode == 1 && elem->op != 0)
		new[i++] = '\"';
	new[i] = '\0';
	return (new);
}

char **ft_list_to_tab(t_env *lst, int mode, int erase)
{
	int i;
	char **tab;
	t_env *current;

	i = 0;
	if (!(tab = malloc(sizeof(char *) * (ft_envsize(lst) + 1))))
		return (NULL);
	current = lst;
	while (current != NULL)
	{
		if ((mode == 0 && current->op != 0 && current->value) || mode == 1)
			tab[i++] = ft_data_to_string(current, mode);
		current = current->next;
	}
	tab[i] = NULL;
	if (erase == 1)
		free_vars(lst);
	return (tab);
}