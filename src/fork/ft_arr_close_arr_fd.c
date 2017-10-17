/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_close_arr_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:49:48 by alex              #+#    #+#             */
/*   Updated: 2017/10/17 04:25:29 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** close the fd of a list of t_arr
*/

int	ft_arr_close_arr_fd(t_arr_fd *arr_fd)
{
	ft_arr_close_fd(arr_fd->arr_fd_stdout);
	ft_arr_close_fd(arr_fd->arr_fd_stderr);
	ft_arr_close_fd(arr_fd->arr_fd_stdin);
	return (EXIT_SUCCESS);
}
