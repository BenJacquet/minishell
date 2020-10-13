/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:46:15 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/13 17:46:54 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_exec(t_all *all, char *exec, char **args, char **envp)
{
	int		ret;
	int		status;
	pid_t	child_pid;

	ret = 0;
	status = 0;
	envp = ft_list_to_tab(all->env, 0, 0);
	if ((child_pid = fork()) == 0)
	{
		status = execve(exec, args, envp);
		if (status == -1)
			ft_put_error(strerror(errno), exec, 1);
	}
	else
		waitpid(child_pid, &ret, 0);
	update_return(all, (ret / 256));
	free_tab(envp);
	free(exec);
	return (1);
}
