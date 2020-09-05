/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:01:11 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/05 17:46:57 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_exists(char *var, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(var, env->name) == 0)
            return (1);
        env = env->next;
    }
    return (0);
}

/*int     expand_token(t_env *var, t_all *all)
{
    int i;
	char *new;

	new = value;
    i = 0;
    if (value)
    {
		while (value[i])
        if (ft_strlen(token) == 1)
            return (1);
        else
        {
            if (ft_strlen(*token) >= 2 && env_exists(*token + 1, all->env))
                *token = ft_getenv(*token + 1, ft_list_to_tab(all->env));
        }
    }
    return (0);
}*/