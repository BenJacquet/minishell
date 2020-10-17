/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 16:18:54 by jabenjam          #+#    #+#             */
/*   Updated: 2020/10/17 19:54:55 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <dirent.h>
# include <stddef.h>
# include <fcntl.h>
# include "GNL/get_next_line.h"
# include "libft/libft.h"

int				g_builtin;
int				g_freete;
int				g_gnl;

typedef	struct s_red
{
	int			red;
	int			fd;
	int			last;
	char		*file;
	void		*next;
}				t_red;

typedef struct	s_tok
{
	char		*value;
	int			beg;
	int			end;
	int			ignore;
	int			whole;
	void		*previous;
	void		*next;
}				t_tok;

typedef struct	s_env
{
	char		*name;
	char		*value;
	int			op;
	void		*next;
}				t_env;

typedef struct	s_all
{
	t_env		*env;
	t_env		*ret;
	int			*shouldi;
	char		*buff;
	char		*oldbuff;
	char		**dir;
	char		**pdir;
	char		**xdir;
	char		*exec;
	int			here;
	int			*dol;
	int			igno;
	int			i;
	int			j;
	int			data;
	int			stop;
	int			pipe;
	int			tube;
	int			countpipe;
	int			fds[2];
	int			fds_backup[2];
	int			p_fds[2];
	int			red;
	int			mask;
	int			env_replaced;
	t_tok		*toks;
	t_red		*reds;
}				t_all;

/*
** -------------CHARLES---------------------------------------------------------
*/

int				cnt(int i, t_all *all, int here);
int				get_dir();
int				end(char *buff, t_all *all);
int				cd(char **dir, t_all all);
int				check(char *buff, t_all *all);
int				checkonlyret(char *buff, t_all *all);
int				checkquote(char *buff);
int				freelance(t_all *all, char **env);
int				freedir(char **dir);
char			**newdir(char **dir, char *buff);
int				pwd(char *buff);
int				echo(t_all all);
int				checkdquote(char *buff);
int				checksquote(char *buff);
char			*ft_strncpy(char *dest, const char *src, int dstsize);
int				pipecount(t_all all,char *str, char c);
char			**ft_splitmini(char *s, char c);
int				counttoken(t_all *all);
void			dolar(t_all *all);
int				join(t_all *all, char *buff, int inc, char quote);
int				silence(char *buff);
int				ifjoin(t_all *all, char *buff, int *inc, char quote);
int				noquote(t_all *all, char *buff, int *inc);
char			**newdirquote(char **dir, int count);
int				joinquote(t_all *all);
void			joinjoin(t_all *all, char *buff, int *inc, int i);
int				crontold(t_all *all);
int				croco(t_all *all, char *buff, int len, int inc);
int				initcroco(t_all *all, int here);
int				parse_command(t_all *all, char **env);
int				parse_command2(t_all *all);
char			*ft_strncat(char *s1, char *s2, int len);
void			init_all(t_all *all, char **env, int ac, char **av);
int				signal_manager(t_all *all);
int				letsgnl(t_all *all);
int				multidir(t_all *all);
int				pipeornotpipe(t_all *all, char ***env);
void			writenotfound(t_all *all);

/*
** -------------BEN------------------------------------------------------------
*/

char			*get_path(t_all *all);
char			*find_dir(t_all *all, char **path, DIR **dir);
char			*find_exec(t_all *all, DIR *dir, char *path);
char			*make_exec(t_all *all, char *path);
int				run_command(t_all *all);
int				fork_command(t_all *all, char **env);
int				is_binary(t_all *all);
int				run_exec(t_all *all, char *exec, char **args);
int				run_exec_forked(t_all *all, char *exec, char **args);
char			*ft_getenv(t_all *all, char *name, int mode);
char			*ft_getenv2(char *name, t_env *current, int mode);
void			ft_putenv(t_env *env);
int				ft_export_core(t_all *all);
int				ft_export_null(t_env *env);
void			ft_export_edit(t_env *var, t_env *env);
int				ft_export_check_name(char *var);
t_env		 	*ft_export_find_name(t_env *var, t_env *env);
void			ft_unset_core(t_all *all);
int				ft_unset_check_name(char *var);
t_env			*ft_unset_find_name(char *var, t_env *current);
void			ft_puttab(char **tab);
char			**tab_dup(char **tab);
void			free_tab(char **tab);
int				ft_tablen(char **tab);
int				ft_varlen(char *var, int mode);
int				ft_tokslen(t_tok *toks);
void			store_variable(char *var, t_env *elem);
t_env			*ft_tab_to_list(char **tab, int erase);
char			**ft_list_to_tab(t_env *lst, int mode, int erase);
int				get_op(char *var);
t_env			*elem_dup(t_env *elem);
t_env			*new_elem(char *var);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoinf(char *s1, char *s2);
int				ft_put_error(char *error, char *var, int mode);
int				ft_check_name(char *var);
int				expand_value(t_env *var, t_all *all);
char			*get_new_value(t_all *all, t_env *var, int len);
t_env			*env_exists(char *name, t_env *env);
int				builtins_env(t_all *all);
int				builtins_others(t_all *all);
int				io_manager_dup_replace(t_all *all);
int				io_manager_dup_restore(t_all *all);
int				handle_redirections(t_all *all);
int				which_redirection(t_all *all, int *start);
char			*get_filename(t_tok **toks, int *start);
char			*ft_dup_until_red(char *src);
void			process_reds(t_all *all, int mask);
t_red			*find_last_in(t_red *reds);
void			free_red(t_red *red);
t_red			*new_red(t_red *head, int red, char **file);
int				ft_isinset(const char *set, char c);
t_tok			*convert_tokens_lst(char **cmd, int *shouldi);
char			**convert_tokens_tab(t_tok *lst);
char			*clean_token(t_tok *tok);
t_tok			*new_token(char *token, t_tok *previous, int whole);
void			reset_fds(t_all *all);
int				no_command(t_all *all, int mode);
void			free_var(t_env *var);
void			free_vars(t_env	*vars);
void			free_tokens(t_tok *toks);
int				update_return(t_all *all, int new);
char			**update_env(t_all *all, char **old);
int				crocodir(t_all *all);

#endif
