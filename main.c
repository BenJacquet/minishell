/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:09:45 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/04 16:48:26 by jabenjam         ###   ########.fr       */
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
    write(1, " : ", 3);
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

	pwd = getcwd(pwd,0);

	len = strlen(pwd);
//	printf("%det d{%s}\n", len, pwd);
//	i = chdir(av[1]);
	free(pwd);
	pwd = getcwd(pwd, 40);
//	printf("%det d{%s}\n", i, pwd + len);
	//write(1, pwd, len);
    get_dir();
	write(1, " -> :", 5);
	get_next_line(0,&buff);
	lenw = strlen(pwd);
	while(strcmp(buff,"ex7") != 0)
	{

	//write(1, "bonjours", 9);
//	write(1, pwd, len);
//	write(1, " -> :", 5);
	pwd = getcwd(pwd,80);
	len = strlen(pwd);
	dir = ft_split(buff, ' ');
	if(ft_strncmp(dir[0], "cd", 2) == 0)
	{
		i = chdir((dir[1]));
		pwd = getcwd(pwd, 80);
		lenw = strlen(pwd);
		len = lenw;
	}
//	printf("%s", pwd);
	else
		system(buff);
	//write(1, pwd, len);
    get_dir();
	write(1, " -> :", 5);
//	write(1, "bonjours", 9);
		pwd = getcwd(pwd, 80);
//	printf("%s", pwd + len);
	lenw = strlen(pwd);
//	write(1, pwd + len , lenw - len);
	free(buff);
	get_next_line(0,&buff);

	}
	free(buff);
	printf("%s", pwd + len);
	write(1, (pwd + len), lenw - len);
	write(1, "lectured", 8);
//	get_next_line(0,&buff);
/*	while(strcmp(buff,"exit") != 0)
	{
	pwd = getcwd(pwd,80);
	len = strlen(pwd);
//	printf("%s", pwd);
	system(buff);
	i = chdir(buff + 5);
	pwd = getcwd(pwd, 80);
//	printf("%s", pwd + len);
	lenw = strlen(pwd);
	write(1, pwd + len , lenw - len);
	free(buff);
	get_next_line(0,&buff);
	write(1, "bonjours", 9);
	}
*/
	return(i);
}
