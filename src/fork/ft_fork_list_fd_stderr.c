/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_list_fd_stderr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:15:15 by alex              #+#    #+#             */
/*   Updated: 2017/02/07 17:15:39 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * push a fd in a t_arr who contain list of fd for write the stderr
 * and if condition on the t_arr for the stdout
 */
int  ft_fork_list_fd_stderr(
  t_arr *arr_fd_stderr, t_arr *arr_fd_stdout, int **fd_ptr, int c)
{
  int *fd_err;
  int *fd;

  fd = *fd_ptr;
  ft_arr_push(arr_fd_stderr, fd, -1);
  if (c == STDOUT_STDERR_REDIRECT)
  {
    if (!(fd_err = malloc(sizeof(int))))
    {
      return (EXIT_FAILURE);
    }
    *fd_err = *fd;
    ft_arr_push(arr_fd_stdout, fd_err, -1);
  }
  return (EXIT_SUCCESS);
}
