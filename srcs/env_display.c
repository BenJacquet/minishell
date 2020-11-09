/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 21:47:26 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/09 15:05:56 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_putenv(t_all *all)
{
	int		i;
	char	**new;

	i = 0;
	if (ft_tablen(all->dir) > 1)
	{
		update_return(all, 127);
		ft_put_error(strerror(2), all->dir[1], 1, 1);
		return ;
	}
	new = ft_list_to_tab(all->env, 0, 0);
	while (new[i] != 0)
	{
		ft_putstr_fd(new[i++], 1);
		write(1, "\n", 1);
	}
	free_tab(new);
	update_return(all, 0);
}

char	*remove_space(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	while (str[j] != '\0')
	{
		while (str[j] != '\0' && str[j] == ' ' && i == 0)
			j++;
		while (str[j] != '\0' && str[j] != ' ')
			new[i++] = str[j++];
		if (str[j] != '\0' && str[j] == ' ' && (j) < ft_strlen(str))
		{
			new[i++] = ' ';
			while (str[j] != '\0' && str[j] == ' ')
				j++;
		}
	}
	new[i] = '\0';
	free(str);
	return (new);
}

/*
** MODE = 0 : pas de quote donc token tel quel
** MODE = 1 : double quote donc token trim
*/

char	*ft_getenv2(char *name, t_env *current, int mode)
{
	if (!(ft_strcmp(name, current->name)))
	{
		if (mode == 0)
			return (ft_strdup(current->value));
		else
			return (remove_space(ft_strdup(current->value)));
	}
	return (NULL);
}

char	*ft_getenv(t_all *all, char *name, int mode)
{
	char	*value;
	t_env	*current;

	value = NULL;
	if (all->env)
		current = all->env;
	else
		return (ft_strdup("\0"));
	if (name[0] == '?')
		return (ft_strdup(all->ret->value));
	while (current != NULL)
	{
		if (!(ft_strcmp(name, current->name)))
		{
			value = ft_getenv2(name, current, mode);
			break ;
		}
		current = current->next;
	}
	value = (current == NULL ? ft_strdup("\0") : value);
	return (value);
}
