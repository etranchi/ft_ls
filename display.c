/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Etienne <etranchi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 01:30:23 by Etienne           #+#    #+#             */
/*   Updated: 2017/08/05 17:12:17 by etranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					add_option(char c, t_opt **opt)
{
	if (c == 'l')
		(*opt)->l = 1;
	else if (c == 'a')
		(*opt)->a = 1;
	else if (c == 'R')
		(*opt)->rc = 1;
	else if (c == 'r')
		(*opt)->r = 1;
	else if (c == 't')
		(*opt)->t = 1;
	else
	{
		ft_error_option(c);
		exit(0);
	}
}

void					set_opt_dir(t_env *e, int ac, char **av)
{
	int i;
	int j;

	i = 1;
	e->files = NULL;
	e->dir = NULL;
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == '-' && !e->files && !e->dir)
			while (av[i][++j])
				add_option(av[i][j], &e->option);
		else
			add_file_dir(av[i], e);
		i++;
	}
	if (e->files == NULL && e->dir == NULL && e->error == 0)
		add_file_dir(".", e);
}

void					get_end_string(char *path)
{
	int i;

	i = ft_strlen(path) - 1;
	while (path[i] && path[i] != '/')
		i--;
	while (path[++i])
		write(1, &path[i], 1);
}

int						check_permission(char *path, t_env *e)
{
	if (access(path, R_OK) == 0)
		return (1);
	else
	{
		write(1, "ls: ", 4);
		get_end_string(path);
		e->error++;
		write(1, ": Persmission denied\n", 21);
		return (0);
	}
}

int						check_is_link(char *file, char *direc)
{
	DIR				*dirp;
	struct dirent	*dir;
	struct stat		tmp;

	dirp = opendir(direc);
	while ((dir = readdir(dirp)) != NULL)
	{
		if (ft_strcmp(dir->d_name, file) == 0 && dir->d_type == DT_LNK)
		{
			if ((lstat(JOIN(JOIN(direc, "/"), file), &tmp) == 0))
			{
				return (1);
			}
			else
				return (0);
		}
	}
	return (0);
}
