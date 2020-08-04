/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:16:26 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/04 16:33:42 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int get_dir()
{
    char *path;
    char *dir;
    int len;
    int i;

    getcwd(path, 0);
    while (path[i] != '\0')
    {
        if (path[i] == '/')
            dir = path + i + 1;
        i++;
    }
    len = strlen(dir);
    write(1, dir, len);
    write(1, " : ", 3);
    return (0);
}