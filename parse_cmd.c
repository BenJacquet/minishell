/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 15:21:37 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/05 16:41:09 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtins_others(t_all *all)
{
	int pipe_bkp;

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
	int pipe_bkp;

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

int	parse_command(t_all *all, char **env)
{
	if (all->pdir[all->data - all->countpipe] && ft_strlen(all->pdir[all->data - all->countpipe]) > 0)
	{
		if ((!(all->pdir[all->data - all->countpipe])))
		{
			all->countpipe--;
			return (1);
		}
		joinquote(all);
		if (!all->dir[0])
		{
			all->countpipe--;
			return (1);
		}
		for (int j=0;all->dir[j];j++)
			printf("\033[1;35mall->dir[j]=[%s]\n\033[0m",all->dir[j]);
		all->toks = convert_tokens_lst(all->dir);
		handle_redirections(all);
		all->dir = convert_tokens_tab(all->toks);
		io_manager_dup(all, 1);
		if (all->dir[0] && (ft_strlen(all->pdir[all->data - all->countpipe]) > 0 &&
					((ft_strcmp(all->dir[0], "cd") == 0) ||
					 ft_strcmp(all->dir[0], "pwd") == 0 ||
					 ft_strcmp(all->dir[0], "echo") == 0)))
			return (builtins_others(all));
		else if (all->dir[0] && (ft_strlen(all->pdir[all->data - all->countpipe]) > 0 &&
					((ft_strcmp(all->dir[0], "env") == 0) ||
					 ft_strncmp(all->pdir[all->data - all->countpipe], "unset", 5) == 0 ||
					 ft_strncmp(all->pdir[all->data - all->countpipe], "export", 6) == 0)))
			return (builtins_env(all));
		else if ((all->exec = get_path(all)) != NULL)
		{
			run_exec(all, all->exec, all->dir, env);
			all->countpipe--;
			return (1);
		}
	}
	//	printf(" parse[%s]\n" , all->pdir[all->data - all->countpipe]);
	return (0);
}

