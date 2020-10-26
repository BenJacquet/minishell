/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:46:15 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/26 19:38:10 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_exec(t_all *all, char *exec, char **args)
{
	int		ret;
	int		status;
	char	**envp;

	ret = 0;
	status = 0;
	envp = ft_list_to_tab(all->env, 0, 0);
	status = execve(exec, args, envp);
	if (status == -1)
		ft_put_error(strerror(errno), exec, 1);
	free_tab(envp);
	return (1);
}

int		action(t_all *all, char ***env, int fd[all->tube][2])
{
	if (all->countsmc > 0)
	{
		parse_command(all, *env, fd);
		*env = update_env(all, *env);
		g_builtin = 0;
	}
	return (0);
}

int		multidir(t_all *all, char ***env, int fd[all->tube][2])
{
	all->here = 0;
	while (all->here <= all->tube)
	{
		joinquotev2(all);
		if (all->here == 0)
			all->around = 1;
		else if (all->here == all->tube)
			all->around = 0;
		else
			all->around = 2;
		action(all, env, fd);
		all->here++;
	}
	all->countsmc--;
	all->tube = 0;
	return (0);
}