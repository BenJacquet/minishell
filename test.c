/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:31:57 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/16 15:10:20 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pipes_manager2(t_all *all, char **execs, int pipes, char **envp)
{
	int		status;
	pid_t	pid;
	int		ret;
	int		fds[pipes][2];

	status = 0;
	ret = 0;
	for (int i = 0; i < pipes ; i++)
		pipe(fds[i]);
	for (int i = 0;all->cmds[i];i++)
	{
		if ((pid = fork()) == 0)
		{
			status = execve(execs[i], all->cmds[i], envp);
			if (status == -1)
				ft_put_error(strerror(errno), execs[i], 1);
		}
		else
			waitpid(pid, &ret, 0);
	}
	update_return(all, (ret / 256));
	free(envp);
	return (0);
}

int		pipes_manager(t_all *all)
{
	int		pipes = ttablen(all->cmds);
	char	**execs;

	printf("pipes=[%d]\n", pipes);

	execs = malloc(sizeof(char *) * (pipes + 1));
	for (int i = 0;all->cmds[i]; i++)
	{
		all->dir = all->cmds[i];
		execs[i] = get_path(all);
		printf("execs[%d]=[%s]\n", i, execs[i]);
	}
	pipes_manager2(all, execs, pipes, ft_list_to_tab(all->env, 0, 0));
	exit(0);
}
