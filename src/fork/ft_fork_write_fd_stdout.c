/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_write_fd_stdout.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 08:33:53 by alex              #+#    #+#             */
/*   Updated: 2017/03/17 12:12:14 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_fork_write_fd_stdout(
	t_tab_tube *array_tube, t_tube *tab_tube, t_arr_fd *arr_fd, t_fork *st_fork)
{
	char			*buff;
	int				rd;

	buff = ft_strnew(st_fork->len_stdout);
	while ((rd = read(
		array_tube->tube_fork_stdout[0], buff, st_fork->len_stdout)))
	{
		if (rd < 0)
			break ;
		if (st_fork->i < st_fork->nb_pipe && !st_fork->err)
			write(tab_tube[st_fork->i].tube[1], buff, st_fork->len_stdout);
		if (arr_fd->arr_fd_stdout->length)
			ft_fork_write_list_fd(
				arr_fd->arr_fd_stdout, buff, st_fork->len_stdout);
		if (!arr_fd->arr_fd_stdout->length && st_fork->i >= st_fork->nb_pipe)
			write(STDOUT, buff, st_fork->len_stdout);
	}
	ft_str_free(&buff);
	return (EXIT_SUCCESS);
}
