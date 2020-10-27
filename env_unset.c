/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 12:35:39 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/27 16:14:42 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_unset_find_name(char *var, t_env *current)
{
	t_env	*backup;
	t_env	*head;

	head = current;
	backup = current;
	if (ft_strcmp(var, current->name) == 0)
	{
		if (current->next)
			backup = current->next;
		free_var(current);
		return (backup);
	}
	while (current)
	{
		backup = (current->next ? current->next : current);
		if (ft_strcmp(var, backup->name) == 0)
		{
			current->next = backup->next;
			free_var(backup);
		}
		current = current->next;
	}
	return (head);
}

int		ft_unset_check_name(char *var)
{
	int		i;

	i = 0;
	if (var[i] != '\0')
	{
		if (ft_isdigit(var[i]) || var[i] == '=' ||
			(!ft_isalnum(var[i]) && var[i] != '_'))
		{
			
			return (ft_put_error("not a valid identifier", var, 1));
		}
		while (ft_isalnum(var[i]) || var[i] == '_')
			i++;
		if (var[i] != '\0')
		{
			return (ft_put_error("not a valid identifier", var, 1));
		}
		else
			return (0);
	}
	return (1);
}

void	ft_unset_core(t_all *all)
{
	int		i;

	i = 0;
	if (!all->dir[1])
		return ;
	while (all->dir[i + 1])
	{
		if (ft_unset_check_name(all->dir[i + 1]) == 0)
		{
			all->env = ft_unset_find_name(all->dir[i + 1], all->env);
			update_return(all, 0);
		}
		else
			update_return(all, 1);
		i++;
	}
	return ;
}
