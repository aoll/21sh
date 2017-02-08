/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_init_arr_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:58:18 by alex              #+#    #+#             */
/*   Updated: 2017/02/08 13:00:04 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int  ft_fork_init_arr_fd(t_arr_fd *arr_fd)
{
  if (!arr_fd)
  {
    return (EXIT_FAILURE);
  }
  if (!(arr_fd->arr_d_end_word = ft_arr_new(1, sizeof(char *))))
  {
    return (EXIT_FAILURE);
  }
  if (!(arr_fd->arr_fd_stdin = ft_arr_new(1, sizeof(int *))))
  {
    ft_arr_free_arr_fd(arr_fd);
    return (EXIT_FAILURE);
  }
  if (!(arr_fd->arr_fd_stderr = ft_arr_new(1, sizeof(int *))))
  {
    ft_arr_free_arr_fd(arr_fd);
    return (EXIT_FAILURE);
  }
  if (!(arr_fd->arr_fd_stdout = ft_arr_new(1, sizeof(int *))))
  {
    ft_arr_free_arr_fd(arr_fd);
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
