/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:21:37 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/10 13:17:27 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtins_others(t_all *all)
{
	int	pipe_bkp;

	pipe_bkp = all->countpipe;
	if (ft_strcmp(all->dir[0], "cd") == 0)
	{
		all->ret->value = ft_itoa(cd(all->dir, *all));
		all->countpipe--;
	}
	else if (ft_strcmp(all->dir[0], "pwd") == 0)
	{
		all->ret->value = ft_itoa(pwd(all->buff));
		all->countpipe--;
	}
	else if (ft_strcmp(all->dir[0], "echo") == 0)
	{
		all->ret->value = ft_itoa(echo(*all));
		all->countpipe--;
	}
	return (all->countpipe != pipe_bkp ? 1 : 0);
}

int		builtins_env(t_all *all)
{
	int	pipe_bkp;

	pipe_bkp = all->countpipe;
	if (ft_strcmp(all->dir[0], "export") == 0)
	{
		ft_export_core(all);
		all->countpipe--;
	}
	else if (ft_strcmp(all->dir[0], "unset") == 0)
	{
		ft_unset_core(all);
		all->countpipe--;
	}
	else if (ft_strcmp(all->dir[0], "env") == 0)
	{
		ft_putenv(all->env);
		all->countpipe--;
	}
	return (all->countpipe != pipe_bkp ? 1 : 0);
}

int		parsincomd(t_all *all, char **env)
{
	int here;

	here = all->data - all->countpipe;
	if (all->dir[0] && 
			((ft_strcmp(all->dir[0], "cd") == 0) ||
			ft_strcmp(all->dir[0], "pwd") == 0 ||
			ft_strcmp(all->dir[0], "echo") == 0))
		return (builtins_others(all));
	else if ( all->dir[0] &&
			((ft_strcmp(all->dir[0], "env") == 0) ||
			ft_strncmp(all->pdir[here], "unset", 5) == 0 ||
			ft_strncmp(all->pdir[here], "export", 6) == 0))
		return (builtins_env(all));
	else if ((all->exec = get_path(all)) != NULL)
	{
		builtin = 2;
		run_exec(all, all->exec, all->dir, env);
		all->countpipe--;
		return (1);
	}
	return (0);
}

int		parse_command(t_all *all, char **env)
{
	printf("pdir=%s\n", all->pdir[all->data - all->countpipe]);
	if (all->pdir[all->data - all->countpipe] &&
			ft_strlen(all->pdir[all->data - all->countpipe]) > 0)
	{
		joinquote(all);
		if (!all->dir[0] || ft_strlen(all->dir[0]) == 0)
		{
			all->countpipe--;
			return (1);
		}
		all->toks = convert_tokens_lst(all->dir);
		handle_redirections(all);
		all->dir = convert_tokens_tab(all->toks);
		printf("AFTER CONVERT: all->dir=[%p]\nall->dir[0]=[%s]", all->dir, all->dir[0]);
		io_manager_dup(all, 1);
		return (parsincomd(all, env));
	}
	else
	{
		all->countpipe--;
		return (1);
	}
	return (0);
}
