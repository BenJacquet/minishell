/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:31:57 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/22 17:12:39 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fds(int in, int out)
{
	dup2(in, STDIN_FILENO);
	close(in);
	dup2(out, STDOUT_FILENO);
	close(out);
}

void	manage_pipes_2(int fd[2][2], int around, int num)
{
	if (around == 0)
	{
		close(fd[num - 1][0]);
	}
	if (around == 1)
	{
		close(fd[num][1]);
	}
	if (around == 2)
	{
		close(fd[num - 1][0]);
		close(fd[num][1]);
	}
}

void	manage_pipes_1(int fd[2][2], int around, int num)
{
	if (around == 2)
	{
		dup2(fd[num - 1][0], STDIN_FILENO);
		dup2(fd[num][1], STDOUT_FILENO);
	}
	else if (around == 0)
	{
		dup2(fd[num - 1][0], STDIN_FILENO);
	}
	else if (around == 1)
	{
		dup2(fd[num][1], STDOUT_FILENO);
	}
	for (int j = 0; j < 2 ; j++)
	{
		close(fd[j][1]);
		close(fd[j][0]);
	}
}

int		main(int ac, char **av, char **env)
{
	int		pip[2][2];
	int		i = 0;
	int		pid = 0;
	(void)ac;
	(void)av;
	char **cmd1 = ft_split("/bin/ls",' ');
	char **cmd2 = ft_split("/bin/cat /sgoinfre/goinfre/Perso/jabenjam/file1",' ');
	char **cmd3 = ft_split("/usr/bin/wc",' ');
	char ***cmds;

	cmds = malloc(sizeof(char**) * 4);
	cmds[0] = cmd1;
	cmds[1] = cmd2;
	cmds[2] = cmd3;
	cmds[3] = NULL;

	int around[3];

	around[0] = 1;
	around[1] = 2;
	around[2] = 0;

	int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);
	for (int j = 0; j < 2; j++)
	{
		printf("opened pipe number %d\n", j);
		pipe(pip[j]);
	}
	while (cmds[i])
	{
		if ((pid = fork()) == 0)
		{
			manage_pipes_1(pip, around[i], i);
			write(2, "exec: ", 6);
			write(2, cmds[i][0], strlen(cmds[i][0]));
			write(2, "\n", 1);
			execve(cmds[i][0], cmds[i], env);
			exit(1);
		}
		else
		{
			waitpid(pid, NULL, 0);
			manage_pipes_2(pip, around[i], i);
		}
		i++;
	}
}
