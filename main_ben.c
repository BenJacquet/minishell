/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ben.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:12:42 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/04 16:34:15 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "GNL/get_next_line.h"
#include "GNL/get_next_line.c"
#include "GNL/get_next_line_utils.c"
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

int manager(char *input)
{
    system(input);
    get_dir();
    return (0);
}

int main_loop()
{
    char *input;
    char *path;
    int out;

    input = malloc(4096);
    get_dir();
    while (get_next_line(0, &input) != 0)
        manager(input);
    return (0);
}

int main(int ac, char **av)
{
    while (main_loop() == 0)
    return (0);
}