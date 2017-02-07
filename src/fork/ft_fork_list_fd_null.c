/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_list_fd_null.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 16:30:34 by alex              #+#    #+#             */
/*   Updated: 2017/02/07 16:31:03 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int  ft_fork_list_fd_null(
  char **cmd, int i, char **name_file, char **error_ptr)
{
  struct stat buf;
  char *tmp;

  tmp = *cmd;
  tmp[i] = SPACE_SEPARATOR;
  lstat(*name_file, &buf);
  if (*error_ptr)
    free(*error_ptr);
  if (S_ISDIR(buf.st_mode))
  {
    *error_ptr = ft_strdup("21sh: it is a directory: ");
  }
  else
  {
    *error_ptr = ft_strdup("21sh: permission denied: ");
  }
  *error_ptr = ft_strjoin_free(error_ptr, *name_file);
  *error_ptr = ft_strjoin_free(error_ptr, "\n");
  free(*name_file);
  return (EXIT_SUCCESS);
}
