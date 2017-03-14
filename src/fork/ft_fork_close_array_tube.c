/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_close_array_tube.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:11:43 by alex              #+#    #+#             */
/*   Updated: 2017/02/08 15:13:29 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * close the fd from a list of tube
 */
int  ft_fork_close_array_tube(t_tab_tube *array_tube)
{
  close(array_tube->tube_fork_stdout[0]);
  close(array_tube->tube_fork_stdout[1]);
  close(array_tube->tube_fork_stderr[0]);
  close(array_tube->tube_fork_stderr[1]);
  close(array_tube->tube_fork_stdout_tmp[0]);
  close(array_tube->tube_fork_stdout_tmp[1]);
  close(array_tube->tube_fork_stderr_tmp[0]);
  close(array_tube->tube_fork_stderr_tmp[1]);
  close(array_tube->tube_fork_stdin[0]);
  close(array_tube->tube_fork_stdin[1]);
  return (EXIT_SUCCESS);
}
