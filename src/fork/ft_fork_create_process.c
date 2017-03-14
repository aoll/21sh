/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_create_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 12:46:21 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 18:29:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * create_process and exec commande
 */
int  ft_fork_create_process(
  t_fork *st_fork, t_arr_fd *arr_fd, t_tab_tube *array_tube, t_tube *tab_tube)
{
  pid_t pid;

  pid = 0;
  if ((pid = fork()) == -1)
  {
    return (EXIT_FAILURE);
  }
  if (!pid)
  {
    ft_fork_pid_son(st_fork, arr_fd, array_tube);
  }
  else if (pid)
  {
    ft_fork_father(st_fork, tab_tube, array_tube, arr_fd);
  }
  return (EXIT_SUCCESS);
}
