/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_set_tube_father.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 12:24:58 by alex              #+#    #+#             */
/*   Updated: 2017/05/18 16:35:23 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_fork_set_tube_father_is_fd(t_arr *arr, int fd_target)
{
	int *fd;
	int i;
	int c;

	i = 0;
	c = 0;
	while (i < (int)arr->length)
	{
		fd = *(int **)((unsigned char *)arr->ptr + i * arr->sizeof_elem);
		if (*fd == fd_target)
		{
			c++;
		}
		i++;
	}
	return (c);
}

void		ft_fork_set_tube_father(
	t_fork *st_fork, t_tab_tube *array_tube, t_tube *tab_tube, t_arr_fd *arr_fd)
{
	close(array_tube->tube_fork_stdout_tmp[1]);
	close(array_tube->tube_fork_stderr_tmp[1]);
	st_fork->len_stderr = 0;
	st_fork->len_stdout = 0;
	if (ft_fork_set_tube_father_is_fd(arr_fd->arr_fd_stdout, -2))
		st_fork->len_stderr += ft_fork_write_tube(
			array_tube->tube_fork_stderr[1],
			array_tube->tube_fork_stdout_tmp[0]);
	st_fork->len_stdout += ft_fork_write_tube(
		array_tube->tube_fork_stdout[1], array_tube->tube_fork_stdout_tmp[0]);
	if (ft_fork_set_tube_father_is_fd(arr_fd->arr_fd_stderr, -1))
		st_fork->len_stdout += ft_fork_write_tube(
			array_tube->tube_fork_stdout[1],
			array_tube->tube_fork_stderr_tmp[0]);
	st_fork->len_stderr += ft_fork_write_tube(
		array_tube->tube_fork_stderr[1], array_tube->tube_fork_stderr_tmp[0]);
	close(array_tube->tube_fork_stderr[1]);
	close(array_tube->tube_fork_stdout[1]);
	if (!ft_fork_set_tube_father_is_fd(arr_fd->arr_fd_stdout, -10))
		ft_fork_write_fd_stdout(array_tube, tab_tube, arr_fd, st_fork);
	if (!ft_fork_set_tube_father_is_fd(arr_fd->arr_fd_stderr, -10))
		ft_fork_write_fd_stderr(array_tube, arr_fd, st_fork);
}
