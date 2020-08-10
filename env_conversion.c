/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:31:34 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/10 16:56:26 by jabenjam         ###   ########.fr       */
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

int	ft_envsize(t_env *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_env *new_elem(char *var)
{
    int i;
    int j;
    t_env *elem;

    i = 0;
    j = 0;
    elem = malloc(sizeof(t_env));
    if (!(elem->name = malloc(sizeof(char) * ft_varlen(var, 0) + 1)))
        return (NULL);
    while (var[i] != '\0' && var[i] != '=' && var[i] != '+')
    {
        elem->name[i] = var[i];
        i++;
    }
    elem->name[i] = '\0';
    if (var[i])
        i++;
    if (!(elem->value = malloc(sizeof(char) * ft_varlen(var, 1) + 1)))
        return (NULL);
    while (var[i] != '\0')
        elem->value[j++] = var[i++];
    elem->value[j] = '\0';
    elem->next = NULL;
    return (elem);
}

t_env *ft_tab_to_list(char **tab)
{
    int i;
    t_env *head;
    t_env *current;

    i = 0;
    current = new_elem(tab[i++]);
    head = current;
    while (tab[i] != NULL)
    {
        current->next = new_elem(tab[i++]);
        current = current->next;
    }
    ft_list_to_tab(head);
    return (head);
}

char *ft_data_to_string(t_env *elem)
{
    char *new;
    int len;
    int i;
    int j;

    i = 0;
    j = 0;
    len = ft_strlen(elem->name) + ft_strlen(elem->value) + 1;
    if (!(new = calloc(sizeof(char), len + 1)))
        return (NULL);
    while (elem->name[j] != '\0')
        new[i++] = elem->name[j++];
    new[i++] = '=';
    j = 0;
    while (elem->value[j] != '\0')
        new[i++] = elem->value[j++];
    new[i] = '\0';
    return (new);
}

char **ft_list_to_tab(t_env *lst)
{
    int i;
    char **tab;
    t_env *current;
    t_env *bkp;

    i = 0;
    if (!(tab = malloc(sizeof(char *) * ft_envsize(lst) + 1)))
        return (NULL);
    current = lst;
    while (current != NULL)
    {
        bkp = current;
        tab[i++] = ft_data_to_string(current);
        current = current->next;
        free(bkp);
    }
    tab[i] = 0;
    return (tab);
}