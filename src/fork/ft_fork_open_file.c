/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_open_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 10:05:21 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 10:08:18 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * open or create file
 */
int  ft_fork_open_file(const char **cmd, t_arr_fd *arr_fd)
{
  char **cmd_tmp;
  char *error_ptr;

  cmd_tmp = NULL;
  error_ptr = NULL;
  cmd_tmp = ft_array_str_dup(cmd);
  ft_fork_list_fd_tmp(cmd_tmp, arr_fd, &error_ptr);
  ft_str_free(&error_ptr);
  ft_array_free(&cmd_tmp);
  return (EXIT_SUCCESS);
}
