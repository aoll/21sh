/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_is_stdin_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:48:10 by alex              #+#    #+#             */
/*   Updated: 2017/05/17 12:38:54 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** check if some fd is present and read and write if is the case
*/

int	ft_fork_is_stdin_fd(
	t_fork *st_fork, t_tube *tab_tube, t_arr_fd *arr_fd, t_tab_tube *array_tube)
{
	//fork !!!!!!!!!!!!!!!!!!!!
	pid_t			pid;
	int status;

//	status = 0;
	pid = 0;

	if ((pid = fork()) == -1)
	{
		return (EXIT_FAILURE);
	}
	if (!pid)
	{
		ft_signal_restore();
		if (arr_fd->arr_fd_stdin->length)
		{
			ft_fork_write_tube_stdin(
			tab_tube, array_tube, st_fork->i, st_fork->nb_pipe);
			ft_fork_read_stdin_file(arr_fd, array_tube);
	//		close(array_tube->tube_fork_stdin[1]);
		}
		exit(EXIT_SUCCESS);
		return (EXIT_SUCCESS);
	}
	else if (pid)
	{
		// wait(&status);
		// if (arr_fd->arr_fd_stdin->length)
		// {
		// 	ft_fork_write_tube_stdin(
		// 	 	tab_tube, array_tube, st_fork->i, st_fork->nb_pipe);
		// 	ft_fork_read_stdin_file(arr_fd, array_tube);
		 	close(array_tube->tube_fork_stdin[1]);
		// }
	}

	// if (arr_fd->arr_fd_stdin->length)
	// {
	// 	ft_fork_write_tube_stdin(
	// 		tab_tube, array_tube, st_fork->i, st_fork->nb_pipe);
	// 	ft_fork_read_stdin_file(arr_fd, array_tube);
	// 	close(array_tube->tube_fork_stdin[1]);
	// }
	return (EXIT_SUCCESS);
}
