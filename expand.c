/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:01:11 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/06 18:47:52 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *env_exists(char *name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env);
		env = env->next;
	}
	return (0);
}

char *get_new_value(t_all *all, t_env *var, int len)
{
	char *new;
	t_env *cor;
	int i;

	i = 0;
	if (!(new = calloc(sizeof(char), len + 1)))
		return (NULL);
	while (var->value[i])
	{
		if (var->value[i] == '$' && ft_strlen(var->value + i) >= 2 &&
			(cor = env_exists(&var->value[i] + 1, all->env)))
		{
			new = ft_strjoinf(new, cor->value);
			i += ft_strlen(cor->name) + 1;
		}
		else
		{
			new[i] = var->value[i];
			i++;
		}
	}
	free(var->value);
	return (new);
}

int expand_value(t_env *var, t_all *all)
{
	int i;
	int len;
	t_env *cor;

	i = 0;
	len = 0;
	if (var->value)
	{
		while (var->value[i])
		{
			if (var->value[i] == '$' && ft_strlen(&var->value[i]) >= 2 &&
				((cor = env_exists(&var->value[i] + 1, all->env)) != NULL))
			{
				len += ft_strlen(cor->value);
				i += ft_strlen(cor->name) + 1;
			}
			else
			{
				i++;
				len++;
			}
		}
		var->value = get_new_value(all, var, len);
	}
	return (0);
}