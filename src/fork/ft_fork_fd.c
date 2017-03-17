/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 11:40:46 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 21:39:27 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** return a case of sucess a fd with the good permission
** -1 if error like not have the permission
*/

static int	ft_fork_fd_simple_redirect(char *name_file)
{
	int				fd;

	if (*name_file == FILE_REDIRECT)
	{
		fd = ft_atoi(name_file + 1);
	}
	else
	{
		fd = open(name_file, O_CREAT | O_RDWR | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	}
	return (fd);
}

static int	ft_fork_fd_double_redirect(char *name_file)
{
	int				fd;

	if (*name_file == FILE_REDIRECT)
	{
		fd = ft_atoi(name_file + 1);
	}
	else
	{
		fd = open(name_file, O_CREAT | O_RDWR | O_APPEND,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	}
	return (fd);
}

static int	ft_fork_fd_left_redirect(char *name_file)
{
	int				fd;

	if (*name_file == FILE_REDIRECT)
	{
		fd = ft_atoi(name_file + 1);
	}
	else
	{
		fd = open(name_file,
			O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	}
	return (fd);
}

static int	ft_fork_fd_switch(char *name_file, int token)
{
	int				fd;

	fd = -1;
	if (token == S_RIGHT_REDIRECT
		|| token == STDOUT_STDERR_REDIRECT || token == STDERR_REDIRECT)
	{
		fd = ft_fork_fd_simple_redirect(name_file);
	}
	else if (token == D_RIGHT_REDIRECT || token == D_STDERR_REDIRECT)
	{
		fd = ft_fork_fd_double_redirect(name_file);
	}
	else if (token == S_LEFT_REDIRECT)
	{
		fd = ft_fork_fd_left_redirect(name_file);
	}
	return (fd);
}

int *ft_fork_fd(char *name_file, int token)
{
	int				fd;
	int				*fd_ptr;

	if (!(fd_ptr = malloc(sizeof(int))))
	{
		return (NULL);
	}
	*fd_ptr = -1;
	fd = ft_fork_fd_switch(name_file, token);
	if (fd == -1)
	{
		free(fd_ptr);
		fd_ptr = NULL;
		return (NULL);
	}
	if (fd == 1 || fd == 2)
	{
		fd *= -1;
	}
	*fd_ptr = fd;
	return (fd_ptr);
}
