/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 08:51:43 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 08:51:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * exec a builtin in function of the index
 * return 0 if sucess 1 if error
 */
int  ft_builtin_exec(
  t_fork *st_fork, t_arr **env, int fd_stdout, int fd_stderr)
{
  if (!st_fork->index_builtin)
    return (EXIT_FAILURE);
  if (st_fork->index_builtin == B_SETENV)
  {
    ft_builtin_setenv((const char **)st_fork->tab_cmd, env, fd_stderr);
  }
  else if (st_fork->index_builtin == B_UNSETENV)
  {
    ft_builtin_unsetenv((const char **)st_fork->tab_cmd, env, fd_stderr);
  }
  else if (st_fork->index_builtin == B_CD)
  {
    ft_builtin_cd((const char **)st_fork->tab_cmd, env, fd_stderr);
  }
  else if (st_fork->index_builtin == B_ECHO)
  {
    ft_builtin_echo((const char **)st_fork->tab_cmd, env);
  }
  else if (st_fork->index_builtin == B_EXIT)
  {
    ft_builtin_exit(st_fork->tab_cmd, env);
  }
  return (EXIT_SUCCESS);
}
