/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:42:28 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/08 13:46:47 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	if (count == 0)
		count = 1;
	if (size == 0)
		size = 1;
	if (!(ptr = (unsigned char *)malloc(sizeof(size) * count)))
		return (NULL);
	while (count > i)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

int				ft_strdel(char **st)
{
	if (st != NULL)
	{
		free(*st);
		*st = NULL;
	}
	return (0);
}

static char		*new_str(char *st)
{
	if (ft_strchr(st, '\n'))
	{
		ft_strcpy(st, ft_strchr(st, '\n') + 1);
		return (st);
	}
	else if (ft_strlen(st) > 0)
	{
		ft_strcpy(st, ft_strchr(st, '\0'));
		return (st);
	}
	return (NULL);
}

int				get_next_line(int fd, char **line)
{
	char			buff[BUFFER_SIZE + 1];
	char			*tmp;
	static char		*st[MAX];
	int				r;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!(st[fd]) && !(st[fd] = ft_calloc(1, sizeof(int))))
		return (-1);
	while (!(ft_strchr(st[fd], '\n')) && (r = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[r] = '\0';
		tmp = st[fd];
		st[fd] = ft_strjoinn(tmp, buff, r);
		free(tmp);
	}
	tmp = ft_substr(st[fd], 0, ft_strlen(st[fd]));
	*line = tmp;
	tmp = NULL;
	free(tmp);
	tmp = NULL;
	if (ft_strchr(st[fd], '\n') == NULL)
		return (ft_strdel(&st[fd]));
	return ((new_str(st[fd]) == NULL) ? 0 : 1);
}
