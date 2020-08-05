/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:18:54 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/05 14:48:06 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "GNL/get_next_line.h"
#include "libft/libft.h"



int     get_dir();
int		end(char	*buff);
int		cd(char		**dir);
char    *ft_getenv(char *cmd, char **env);
int		check(char *buff);
int		checkquote(char *buff);


#endif

