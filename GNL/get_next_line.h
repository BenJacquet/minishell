/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 19:48:18 by chgilber          #+#    #+#             */
/*   Updated: 2020/08/08 13:46:52 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define MAX 1024
# define BUFFER_SIZE 1024

int				get_next_line(int fd, char **line);
int				ft_strlen(const char *str);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strjoinn(char *s1, char *s2, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strchr(const char *s, int c);
void			*ft_calloc(size_t count, size_t size);
int				ft_strdel(char	**stck);
#endif
