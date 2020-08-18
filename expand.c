/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 17:01:11 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/18 18:02:58 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     expand_token(char **token, t_all *all)
{
    int i;
    char *backup;

    i = 0;
    backup = *token;
    if (*token)
    {
        if (ft_strlen(*token) == 1)
            return (1);
        else
        {
            if (ft_strlen(*token) >= 2)
            *token = ft_getenv(*token + 1, ft_list_to_tab(all->env));
            return (2);
        }
    }
    return (0);
}