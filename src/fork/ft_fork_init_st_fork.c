/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_init_st_fork.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 12:58:38 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 13:01:01 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * init the pointeur to NULL of struct st_fork,
 * init the pointeur env
 * and dup the STD[IN, OUT, ERR] for back afer the finished process
 */
int  ft_fork_init_st_fork(t_fork *st_fork, t_arr **env)
{
  st_fork->env_copy = NULL;
  st_fork->tab_cmd = NULL;
  st_fork->envp = NULL;
  st_fork->error_ptr = NULL;
  st_fork->env = env;
  st_fork->stdin_copy = dup(STDIN);
  st_fork->stdout_copy = dup(STDOUT);
  st_fork->stderr_copy = dup(STDERR);
  return (EXIT_SUCCESS);
}
