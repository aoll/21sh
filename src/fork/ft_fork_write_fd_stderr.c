/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_write_fd_stderr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 09:43:03 by alex              #+#    #+#             */
/*   Updated: 2017/03/17 12:11:56 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_fork_write_fd_stderr(
	t_tab_tube *array_tube, t_arr_fd *arr_fd, t_fork *st_fork)
{
	int				rd;
	char			*buff;

	if (!(buff = ft_strnew(st_fork->len_stderr)))
		return (EXIT_FAILURE);
	while ((rd = read(
		array_tube->tube_fork_stderr[0], buff, st_fork->len_stderr)))
	{
		if (rd < 0)
			break ;
		if (arr_fd->arr_fd_stderr->length)
		{
			ft_fork_write_list_fd(
				arr_fd->arr_fd_stderr, buff, st_fork->len_stderr);
		}
		else if (!arr_fd->arr_fd_stderr->length)
		{
			write(STDERR, buff, st_fork->len_stderr);
		}
	}
	ft_str_free(&buff);
	return (EXIT_SUCCESS);
}
