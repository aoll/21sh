/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_fd_from_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 16:47:13 by alex              #+#    #+#             */
/*   Updated: 2017/02/07 16:47:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int  ft_fork_fd_from_name(int **fd, char **command, char **error_ptr, int i)
{
  char *name_file;
  char *cmd;

  cmd = *command;
  if (!(name_file = ft_fork_name_file(command, i + 1)))
  {
    return (EXIT_FAILURE);
  }
  *fd = ft_fork_fd(name_file, cmd[i]);
  if (*fd == NULL)
  {
    ft_fork_list_fd_null(command, i, &name_file, error_ptr);
    return (EXIT_FAILURE);
  }
  free(name_file);
  return (EXIT_SUCCESS);
}
