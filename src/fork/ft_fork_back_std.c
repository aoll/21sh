/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_back_std.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:03:37 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 13:04:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * dup the copy of std[IN, OUT, ERR] to restore the std
 */
int  ft_fork_back_std(t_fork *st_fork)
{
  dup2(st_fork->stdin_copy, STDIN);
  dup2(st_fork->stdout_copy, STDOUT);
  dup2(st_fork->stderr_copy, STDERR);
  close(st_fork->stdin_copy);
  close(st_fork->stdout_copy);
  close(st_fork->stderr_copy);
  return (EXIT_SUCCESS);
}
