/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:31:34 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/13 17:38:04 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_envsize(t_env *lst)
{
	int		i;

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

char	*ft_data_to_string(t_env *elem, int mode)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(elem->name) + ft_strlen(elem->value) + 1;
	if (!(new = malloc(sizeof(char) * (len + 1 + 2))))
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

char	**ft_list_to_tab(t_env *lst, int mode, int erase)
{
	int		i;
	char	**tab;
	t_env	*current;

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
