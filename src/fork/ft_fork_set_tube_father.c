/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_set_tube_father.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 12:24:58 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 12:27:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
*
*/

int	ft_fork_set_tube_father(
	t_fork *st_fork, t_tab_tube *array_tube, t_tube *tab_tube, t_arr_fd *arr_fd)
{
	close(array_tube->tube_fork_stdout_tmp[1]);
	close(array_tube->tube_fork_stderr_tmp[1]);
	st_fork->len_stdout = ft_fork_write_tube(
		array_tube->tube_fork_stdout[1], array_tube->tube_fork_stdout_tmp[0]);
	st_fork->len_stderr = ft_fork_write_tube(
		array_tube->tube_fork_stderr[1], array_tube->tube_fork_stderr_tmp[0]);
	close(array_tube->tube_fork_stderr[1]);
	close(array_tube->tube_fork_stdout[1]);
	ft_fork_write_fd_stdout(array_tube, tab_tube, arr_fd, st_fork);
	ft_fork_write_fd_stderr(array_tube, arr_fd, st_fork);
	return (EXIT_SUCCESS);
}
