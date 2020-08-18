/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:18:54 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/18 18:17:12 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <dirent.h>
# include "GNL/get_next_line.h"
# include "libft/libft.h"

typedef struct	s_env
{
	char		*name;
	char		*value;
	void		*next;
}				t_env;

typedef struct	s_all
{
	t_env		*env;
	char		*buff;
	char		*oldbuff;
	char		**dir;
	char		**pdir;
	char		*exec;
	int			i;
	int			j;
	int			data;
	int			stop;
	int			pipe;
	int			countpipe;
}				t_all;

/*
** -------------CHARLES---------------------------------------------------------
*/

int				get_dir();
int				end(char *buff);
int				cd(char **dir);
int				check(char *buff);
int				checkquote(char *buff);
int				freelance(char **dir, char *buff);
int				freedir(char **dir);
char			**newdir(char **dir, char *buff);
int				pwd(char *buff);
int				echo(t_all all);
int				checkdquote(char *buff);
int				checksquote(char *buff);
char			*ft_strncpy(char *dest, const char *src, int dstsize);
int				pipecount(t_all all, char c);
char			**ft_splitmini(char *s, char c);


/*
** -------------BEN------------------------------------------------------------
*/

char			*get_path(t_all *all);
char			*find_exec(t_all *all, DIR *dir, char *path);
char			*make_exec(t_all *all, char *path);
int				run_exec(char *exec, char **args, char **envp);
char			*ft_getenv(char *var, char **env);
void			ft_putenv(char **env);
char			**ft_export_core(char *var, char **env);
int				ft_export_null(char **env);
int				ft_export_edit(char *var, t_env *env, int op);
int				ft_export_check_name(char *var);
int				ft_export_find_name(char *var, t_env *env, int op);
char			**ft_unset_core(char *var, char **env);
int				ft_unset_check_name(char *var);
int				ft_unset_find_name(char *var, t_env *current);
char			**tab_dup(char **tab);
void			free_tab(char **tab);
int				ft_tablen(char **tab);
void			store_variable(char *var, t_env *elem);
t_env			*ft_tab_to_list(char **tab);
char			**ft_list_to_tab(t_env *lst);
t_env			*new_elem(char *var);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_varlen(char *var, int mode);
int				ft_put_error(char *error, char *var, int mode);
int				ft_check_name(char *var);
int				expand_token(char **token, t_all *all);
int				env_exists(char *var, t_env *env);

#endif
