/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_pid_son.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:38:59 by alex              #+#    #+#             */
/*   Updated: 2017/10/17 03:27:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_fork_write_from_file(t_arr *arr, int fd_target)
{
	int *fd;

	if (arr->length)
	{
		fd = *(int **)(
			(unsigned char *)arr->ptr + (arr->length - 1) * arr->sizeof_elem);
		dup2(*fd, fd_target);
		close(*fd);
	}
	return (EXIT_SUCCESS);
}

int	ft_fork_write_in_file(t_arr *arr, int fd_target)
{
	int				*fd;
	int				p[2];
	char			*line;

	if (arr->length)
	{
		fd = *(int **)(
			(unsigned char *)arr->ptr + (arr->length - 1) * arr->sizeof_elem);
		// ft_putstr("\nfd: ");ft_putnbr(*fd);ft_putstr(".\n");
		if (*fd == -2 && !fd_target)
		{
			line = NULL;
			char *tmp = ft_strnew(0);
			while (get_next_line(0, &line) > 0) {
				if (line)
				{
					tmp = ft_strjoin_free(&tmp, line);
					tmp = ft_strjoin_free(&tmp, "\n");
					ft_str_free(&line);
				}
			}
			if (line)
			{
				free(line);
			}
			pipe(p);

			ft_putstr_fd(tmp, p[1]);
			close(p[1]);
			dup2(p[0], fd_target);
			close(p[0]);
			free(tmp);
			return (EXIT_SUCCESS);
		}
		if (*fd == -10 )
		{
			*fd = -1;
			pipe(p);
			dup2(p[1], fd_target);
			close(p[1]);
			return (EXIT_SUCCESS);
		}
		else if (*fd < 0)
		{
			*fd *= -1;
		}
		dup2(*fd, fd_target);
		close(*fd);
	}
	return (EXIT_SUCCESS);
}

/*
** is the processus son, set the tube for processus comminucation
** execute the command
*/

int	ft_fork_pid_son(t_fork *st_fork, t_arr_fd *arr_fd, t_tab_tube *array_tube)
{
	char	*path_tmp;
	int		re;

	re = 0;
	ft_signal_restore();

	//waza
	// ft_fork_set_tube(arr_fd, array_tube, st_fork->i, st_fork->nb_pipe);
	ft_fork_is_error_ptr(&st_fork->error_ptr, arr_fd);

	ft_fork_write_in_file(arr_fd->arr_fd_stdout, STDOUT);

	ft_fork_write_in_file(arr_fd->arr_fd_stderr, STDERR);
	ft_fork_write_in_file(arr_fd->arr_fd_stdin, STDIN);

	// ft_fork_read_stdin_file(arr_fd, array_tube);

	// ft_fork_write_in_file(arr_fd->arr_fd_stdin, STDIN);
	// ft_putstr("\nin: ");ft_putnbr(arr_fd->arr_fd_stdin->length);ft_putstr(".\n");

	path_tmp = NULL;
	if (!st_fork->index_builtin && *st_fork->tab_cmd)
	{
		path_tmp = ft_fork_init_path(
			st_fork->env_copy, st_fork->tab_cmd, &st_fork->err);
	}
	if (!st_fork->index_builtin && !st_fork->err && *st_fork->tab_cmd)
		re = ft_fork_son_exec(path_tmp, st_fork->tab_cmd, st_fork->envp);
	ft_str_free(&path_tmp);
	if (re != B_ECHO)
		ft_fork_command_not_found(
			&st_fork->tab_cmd, st_fork->index_builtin, arr_fd);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
