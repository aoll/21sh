/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_is_stdin_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:48:10 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 21:41:01 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** check if some fd is present and read and write if is the case
*/

int	ft_fork_is_stdin_fd(
	t_fork *st_fork, t_tube *tab_tube, t_arr_fd *arr_fd, t_tab_tube *array_tube)
{
	if (arr_fd->arr_fd_stdin->length)
	{
		ft_fork_write_tube_stdin(
		tab_tube, array_tube, st_fork->i, st_fork->nb_pipe);
		ft_fork_read_stdin_file(arr_fd, array_tube);
		close(array_tube->tube_fork_stdin[1]);
	}
	return (EXIT_SUCCESS);
}
