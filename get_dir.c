/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:16:26 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/04 16:16:28 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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