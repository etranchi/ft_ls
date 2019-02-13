/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 23:54:41 by Etienne           #+#    #+#             */
/*   Updated: 2017/07/04 23:54:45 by Etienne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define JOIN(a,b) ft_strjoin(a,b)

# include "libft/libft.h"
# include <stdio.h>
# include <ctype.h>
# include <sys/dir.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <errno.h>

typedef struct		s_opt
{
	int				a;
	int				rc;
	int				r;
	int				l;
	int				t;
}					t_opt;

typedef struct		s_file
{
	char			*path;
	time_t			time;
	struct s_file	*next;
}					t_file;

typedef struct		s_dir
{
	char			*path;
	int				buflen;
	int				total;
	time_t			time;
	struct s_file	*files;
	struct s_dir	*dir;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_env
{
	t_opt			*option;
	t_file			*files;
	t_dir			*dir;
	int				error;
}					t_env;

void				add_option(char c, t_opt **opt);
void				set_opt_dir(t_env *e, int ac, char **av);
void				displayf(t_file **file);
void				display_dir(t_dir **dir, t_opt *option, t_env *e);
void				display_files(t_file **lst, t_opt *option, char *path);
void				displayf_l(t_file **file, char *path);
void				display_name(t_dir *dir);
void				add_lst_file(t_file **file, char *path);
void				add_lst_dir(t_dir **dir, char *path);
void				sort_time(t_file **begin);
void				retrieve_dot_files(t_file **begin);
void				sort_path(t_file **begin);
void				reverse_lst_file(t_file **begin);
void				reverse_lst_dir(t_dir **begin);
void				file_free(t_file *file);
void				dir_free(t_dir *dir);
void				release_lst_dir(t_dir *lst);
int					get_width_buf(t_file *lst);
void				put_total(int total);
void				ft_error_option(char c);
void				release_lst_file(t_file *lst);
int					compare(t_file *curr, t_file *next);
void				put_st_mod(mode_t mode, char *path, char *direc);
void				print_links(nlink_t link);
void				print_user(uid_t user);
void				print_group(gid_t group);
void				display_name(t_dir *dir);
t_file				*create_file(char *path);
t_dir				*create_dir(char *path);
void				add_file_dir(char *path, t_env *e);
int					check_is_link(char *file, char *direc);
int					check_permission(char *path, t_env *e);

#endif
