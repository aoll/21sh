/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_list_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 11:51:20 by alex              #+#    #+#             */
/*   Updated: 2017/05/18 11:51:46 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** in case in sucess return EXIT_SUCCESS else EXIT_FAILURE
** give a list of fd with good right and position cursor
** error if the file can be open
*/

static int	ft_fork_list_fd_switch_right_dup(int fd, t_arr_fd *arr_fd)
{
	int				err;
	int				*f = malloc(sizeof(int));

	ft_putnbr(fd);
	if (fd == -2)
	{
		// *f = 2;
		// ft_arr_push(arr_fd->arr_fd_stdout, f, -1);
		if ((err = ft_fork_list_fd_dup(
			arr_fd->arr_fd_stdout, arr_fd->arr_fd_stderr)))
		{
			return (EXIT_FAILURE);
		}
	}
	else if (fd == -1)
	{
		// *f = -1;
		// ft_arr_push(arr_fd->arr_fd_stderr, f, -1);
		// f = malloc(sizeof(int));
		// *f = 2;
		// ft_arr_push(arr_fd->arr_fd_stderr, f, -1);
		if ((err = ft_fork_list_fd_dup(
			arr_fd->arr_fd_stderr, arr_fd->arr_fd_stdout)))
		{
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	ft_fork_list_fd_switch_right_redirect(
	int c, int **fd, t_arr_fd *arr_fd)
{
	int				err;

	if (c == STDOUT_STDERR_REDIRECT
		|| c == STDERR_REDIRECT || c == D_STDERR_REDIRECT)
	{
		if ((err = ft_fork_list_fd_stderr(
			arr_fd->arr_fd_stderr, arr_fd->arr_fd_stdout, fd, c)))
		{
			return (EXIT_FAILURE);
		}
	}
	else if (c == S_RIGHT_REDIRECT || c == D_RIGHT_REDIRECT)
	{
		// ft_putstr("\nc is redirect");ft_putnbr(**fd);ft_putstr("\n");
		ft_arr_push(arr_fd->arr_fd_stdout, *fd, -1);
	}
	else if (c == S_LEFT_REDIRECT)
	{
		if (**fd != 0 && **fd != 1 && **fd != 2)
			ft_arr_push(arr_fd->arr_fd_stdin, *fd, -1);
		else
		{
			free(*fd);
		}
	}
	return (EXIT_SUCCESS);
}

static int	ft_fork_list_fd_switch_right(
	int **fd_ptr, t_arr_fd *arr_fd, char *cmd, int i)
{
	int				err;
	int				*fd;

	fd = *fd_ptr;
	// if (*fd == -2 || *fd == -1)
	// {
	// 	if ((err = ft_fork_list_fd_switch_right_dup(*fd, arr_fd)))
	// 	{
	// 		return (EXIT_FAILURE);
	// 	}
	// 	return (EXIT_SUCCESS);
	// }
	if ((err = ft_fork_list_fd_switch_right_redirect(cmd[i], fd_ptr, arr_fd)))
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ft_fork_list_fd_is_redirect(int c)
{
	if (c == S_RIGHT_REDIRECT || c == D_RIGHT_REDIRECT
		|| c == STDOUT_STDERR_REDIRECT || c == STDERR_REDIRECT
		|| c == D_STDERR_REDIRECT || c == S_LEFT_REDIRECT)
	{
		// ft_putstr("\nc:");ft_putnbr(c);ft_putstr("\n");
		return (1);
	}
	return (EXIT_SUCCESS);
}

int			ft_fork_list_fd(char **command, t_arr_fd *arr_fd, char **error_ptr)
{
	int				i;
	int				*fd;
	char			*cmd;
	int				err;

	i = -1;
	cmd = *command;
	ft_arr_close_arr_fd(arr_fd);
	// ft_putstr("\n-----------------\nlen stdout");ft_putnbr(arr_fd->arr_fd_stdout->length);ft_putstr("\n");
	// ft_putstr("\nlen stderr");ft_putnbr(arr_fd->arr_fd_stderr->length);ft_putstr("\n");
	while (cmd[++i])
		if (cmd[i] == D_LEFT_REDIRECT)
		{
			if ((err = ft_fork_list_fd_left_redirect(arr_fd->arr_fd_stdin)))
				return (EXIT_FAILURE);
		}
		else if (ft_fork_list_fd_is_redirect(cmd[i]))
		{
			if ((err = ft_fork_fd_from_name(&fd, &cmd, error_ptr, i)))
				return (EXIT_FAILURE);
			if ((err = ft_fork_list_fd_switch_right(&fd, arr_fd, cmd, i)))
				return (EXIT_FAILURE);
			cmd[i] = SPACE_SEPARATOR;
		}
	if (arr_fd->arr_fd_stdout->length)
	{
		int *fd_tmp = *((int **)arr_fd->arr_fd_stdout->ptr);
		*fd = -10;
	}

	return (EXIT_SUCCESS);
}
