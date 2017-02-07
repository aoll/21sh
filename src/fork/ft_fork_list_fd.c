/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_list_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 11:51:20 by alex              #+#    #+#             */
/*   Updated: 2017/02/07 15:57:52 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * in case in sucess return EXIT_SUCCESS else EXIT_FAILURE
 * give a list of fd with good right and position cursor
 * error if the file can be open
 */

static int  ft_fork_list_fd_null(
  char **cmd, int i, char **name_file, char **error_ptr)
{
  struct stat buf;
  char *tmp;

  tmp = *cmd;
  tmp[i] = SPACE_SEPARATOR;
  lstat(*name_file, &buf);
  if (*error_ptr)
  {
    free(*error_ptr);
  }
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

int  ft_fork_list_fd(char **command, t_arr *tab_fd_stdout, t_arr *tab_fd_stderr, t_arr *tab_fd_stdin, char **error_ptr)
{
  char *name_file;
  int i;
  int *fd;
  char *cmd;
  int *fd_err;
  int index;
  int *fd_tmp;
  int *fd_dup;

  i = 0;
  cmd = *command;
  ft_arr_close_fd(tab_fd_stdout);
  ft_arr_close_fd(tab_fd_stderr);
  ft_arr_close_fd(tab_fd_stdin);
  while (cmd[i])
  {
    if (cmd[i] == D_LEFT_REDIRECT)
    {
      if (!(fd_dup = malloc(sizeof(int))))
      {
        return (EXIT_FAILURE);
      }
      *fd_dup = D_LEFT_REDIRECT;
      ft_arr_push(&tab_fd_stdin, fd_dup, -1);
    }
    else if (cmd[i] == S_RIGHT_REDIRECT || cmd[i] == D_RIGHT_REDIRECT || cmd[i] == STDOUT_STDERR_REDIRECT || cmd[i] == STDERR_REDIRECT || cmd[i] == D_STDERR_REDIRECT || cmd[i] == S_LEFT_REDIRECT)
    {

      if (!(name_file = ft_fork_name_file(&cmd, i + 1)))
      {
        return (EXIT_FAILURE);
      }
      fd = ft_fork_fd(name_file, cmd[i]);
      if (fd == NULL)
      {
        ft_fork_list_fd_null(&cmd, i, &name_file, error_ptr);
        return (EXIT_FAILURE);
      }
      free(name_file);
      index = 0;
      if (*fd == -2)
      {
        while (index < (int)tab_fd_stderr->length)
        {
          fd_tmp = *(int **)((unsigned char *)tab_fd_stderr->ptr + index * tab_fd_stderr->sizeof_elem);
          if (!(fd_dup = malloc(sizeof(int))))
          {
            return (EXIT_FAILURE);
          }
          *fd_dup = *fd_tmp;
          ft_arr_push(&tab_fd_stdout, fd_dup, -1);
          index++;
        }
      }
      else if (*fd == -1)
      {
        while (index < (int)tab_fd_stdout->length)
        {
          fd_tmp = *(int **)((unsigned char *)tab_fd_stdout->ptr + index * tab_fd_stdout->sizeof_elem);
          if (!(fd_dup = malloc(sizeof(int))))
          {
            return (EXIT_FAILURE);
          }
          *fd_dup = *fd_tmp;
          ft_arr_push(&tab_fd_stderr, fd_dup, -1);
          index++;
        }
      }
      else if (cmd[i] == STDOUT_STDERR_REDIRECT || cmd[i] == STDERR_REDIRECT || cmd[i] == D_STDERR_REDIRECT)
      {
        ft_arr_push(&tab_fd_stderr, fd, -1);
        if (cmd[i] == STDOUT_STDERR_REDIRECT)
        {
          fd_err = malloc(sizeof(int));
          *fd_err = *fd;
          ft_arr_push(&tab_fd_stdout, fd_err, -1);
        }
      }
      else if (cmd[i] == S_RIGHT_REDIRECT || cmd[i] == D_RIGHT_REDIRECT)
      {
        ft_arr_push(&tab_fd_stdout, fd, -1);
      }
      else if (cmd[i] == S_LEFT_REDIRECT)
      {
        ft_arr_push(&tab_fd_stdin, fd, -1);
      }
      cmd[i] = SPACE_SEPARATOR;
    }
    i++;
  }
  return (EXIT_SUCCESS);
}
