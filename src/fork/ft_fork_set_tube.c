/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_set_tube.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:56:56 by alex              #+#    #+#             */
/*   Updated: 2017/02/08 16:03:21 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** dup and close flux in function of the arr fd
*/

static int	ft_fork_set_tube_stdout(
	t_arr_fd *arr_fd, t_tab_tube *array_tube, int i, int nb_pipe)
{
	if (nb_pipe || arr_fd->arr_fd_stdout->length)
	{
		if (i < nb_pipe && !arr_fd->arr_fd_stdout->length)
		{
			close(array_tube->tube_fork_stdout_tmp[0]);
			dup2(array_tube->tube_fork_stdout_tmp[1], 1);
		}
		if (arr_fd->arr_fd_stdout->length)
		{
			close(array_tube->tube_fork_stdout_tmp[0]);
			dup2(array_tube->tube_fork_stdout_tmp[1], 1);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_fork_set_tube(
	t_arr_fd *arr_fd, t_tab_tube *array_tube, int i, int nb_pipe)
{
	if (arr_fd->arr_fd_stdin->length)
	{
		close(array_tube->tube_fork_stdin[1]);
		dup2(array_tube->tube_fork_stdin[0], 0);
	}
	if (arr_fd->arr_fd_stderr->length)
	{
		close(array_tube->tube_fork_stderr_tmp[0]);
		dup2(array_tube->tube_fork_stderr_tmp[1], 2);
	}
	ft_fork_set_tube_stdout(arr_fd, array_tube, i, nb_pipe);
	return (EXIT_SUCCESS);
}
