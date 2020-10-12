/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 12:59:13 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/11 17:41:21 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tok *toks)
{
	t_tok	*current;
	
	current = NULL;
	while (toks)
	{
		current = toks;
		if (toks->value)
			free(toks->value);
		toks = toks->next;
		free(current);
	}
}

void	free_vars(t_env	*env)
{
	t_env	*current;
	
	current = NULL;
	while (env)
	{
		current = env;
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		env = env->next;
		free(current);
	}
}