/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/04 16:58:43 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "GNL/get_next_line.h"
#include "libft/libft.h"

int get_dir()
{
    char *path;
    char *dir;
    void *bkp;
    int len;

    path = getcwd(path, 0);
    bkp = path;
    while (*path != '\0')
    {
        if (*path == '/')
            dir = ++path;
        path++;
    }
    len = strlen(dir);
    write(1, dir, len);
    free(bkp);
    return (0);
}

int		main(int ac, char **av)
{
	int	i;
	int len;
	int lenw;
	char *pwd;
	char **dir;
	char *buff;

    get_dir();
	write(1, " -> :", 5);
	get_next_line(0,&buff);
	while(strcmp(buff,"exit") != 0)
	{
	dir = ft_split(buff, ' ');
	if(ft_strncmp(dir[0], "cd", 2) == 0)
		i = chdir((dir[1]));
	else
		system(buff);
    get_dir();
	write(1, " -> :", 5);
	free(buff);
	get_next_line(0,&buff);
	}
	free(buff);
	printf("%s", pwd + len);
	write(1, "lectured", 8);
	return(i);
}
