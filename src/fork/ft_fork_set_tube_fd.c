/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_set_tube_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 11:12:04 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 11:16:17 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 *
 */
int  ft_fork_set_tube_fd(
  t_fork *st_fork, t_tab_tube *array_tube, t_arr_fd *arr_fd, char **cmd)
{
  if (st_fork->i)
  {
    ft_fork_close_array_tube(array_tube);
  }
  ft_fork_pipe_array_tube(array_tube);
  st_fork->index_builtin = false;
  st_fork->err = 0;
  ft_str_free(&st_fork->error_ptr);
  st_fork->err = ft_fork_list_fd(cmd, arr_fd, &st_fork->error_ptr);
  if ((st_fork->err = ft_fork_list_d_end_word(
    cmd, arr_fd->arr_d_end_word)))
  {
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
