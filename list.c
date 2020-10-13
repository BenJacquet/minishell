/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 12:59:13 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/13 17:48:01 by jabenjam         ###   ########.fr       */
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

void	free_var(t_env *var)
{
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	free(var);
}

void	free_vars(t_env *vars)
{
	t_env	*current;

	current = NULL;
	while (vars)
	{
		current = vars;
		vars = vars->next;
		free_var(current);
	}
}
