/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_init_env_copy.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:31:44 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 13:36:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * init the env_copy by a dup to the env
 * set the copy if is B_ENV
 */
int  ft_fork_init_env_copy(t_fork *st_fork, t_arr *env, t_tab_tube *array_tube)
{
  if (st_fork->env_copy)
  {
    ft_arr_free(st_fork->env_copy);
    st_fork->env_copy = NULL;
  }
  st_fork->env_copy = ft_arr_dup(env);
  if (st_fork->index_builtin == B_ENV)
  {
    st_fork->index_builtin = ft_builtin_env(
      &st_fork->tab_cmd,
      &st_fork->env_copy,
      array_tube->tube_fork_stdout_tmp[1],
      array_tube->tube_fork_stderr_tmp[1]);
  }
  return (EXIT_SUCCESS);
}
