/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:18:54 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/06 16:45:19 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "GNL/get_next_line.h"
#include "libft/libft.h"

typedef struct s_env
{
    char *name;
    char *value;
    void *next;
} t_env;

int get_dir();
int end(char *buff);
int cd(char **dir);
char *ft_getenv(char *var, char **env);
int ft_export(char *var, char **env);
void ft_putenv(char **env);
void ft_sort_tab(char **env);
char **tab_dup(char **tab);
void free_tab(char **tab);
int ft_tablen(char **tab);
char *ft_find_var(char *var, char **env);
void store_variable(char *var, t_env *elem);
t_env *ft_tab_to_list(char **tab);
char **ft_list_to_tab(t_env *lst);
t_env *new_variable(char *var);
int ft_varlen(char *var, int mode);
int check(char *buff);
int checkquote(char *buff);

#endif
