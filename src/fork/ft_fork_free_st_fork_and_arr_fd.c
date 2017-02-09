/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_free_st_fork_and_arr_fd.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:08:09 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 13:10:53 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * restore the std[IN,OUT,ERR]
 * free the pointeur of the struct st_fork
 * free the pointeur of the structure arr_fd
 */
int  ft_fork_free_st_fork_and_arr_fd(t_fork *st_fork, t_arr_fd *arr_fd)
{
  ft_fork_back_std(st_fork);
  if (st_fork->env_copy)
  {
    ft_arr_free(st_fork->env_copy);
    st_fork->env_copy = NULL;
  }
  ft_arr_close_arr_fd(arr_fd);
  ft_arr_free_arr_fd(arr_fd);
  ft_array_free(&st_fork->envp);
  ft_array_free(&st_fork->tab_cmd);
  ft_str_free(&st_fork->error_ptr);
  return (EXIT_SUCCESS);
}
