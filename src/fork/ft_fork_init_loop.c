/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_init_loop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 10:23:58 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 10:28:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * init the var the fork'loop and create the file for the redirection
 */
int  ft_fork_init_loop(
  t_fork *st_fork, t_arr_fd *arr_fd, const char **cmd, int nb_pipe)
{
  st_fork->nb_pipe = nb_pipe;
  if ((st_fork->err = ft_fork_init_arr_fd(arr_fd)))
  {
    return (EXIT_FAILURE);
  }
  st_fork->i = 0;
  ft_fork_open_file(cmd, arr_fd);
  return (EXIT_SUCCESS);
}
