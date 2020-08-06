/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:31:34 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/06 16:59:01 by jabenjam         ###   ########.fr       */
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
    while (var[i] != '\0' && var[i] != '=')
        i++;
    if (mode == 0)
        return (i);
    while (var[i + j] != '\0')
        j++;
    return (j);
    printf("i=%d j=%d var=%s\n", i, j, var);
}

t_env *new_variable(char *var)
{
    int i;
    int j;
    t_env *elem;

    i = 0;
    j = 0;
    elem = malloc(sizeof(t_env));
    if (!(elem->name = malloc(sizeof(char) * ft_varlen(var, 0) + 1)))
        return (NULL);
    while (var[i] != '\0' && var[i] != '=')
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
    current = new_variable(tab[i++]);
    head = current;
    while (tab[i] != NULL)
    {
        current->next = new_variable(tab[i++]); // trouver pourquoi l'add_back segfault
        current = current->next;
    }
    for (int x = 0; head; x++)
    {
        printf("elem[%d] NAME=%s VALUE=%s\n", x, head->name, head->value);
        head = head->next;
    }
    return (head);
}

/*char **ft_list_to_tab(t_env *lst)
{
    int     i;
    char    **tab;

    i = 0;
    if (!(tab = malloc(sizeof(char*) * ft_lstsize(lst) + 1)))
        return (NULL);
    while ()
}*/