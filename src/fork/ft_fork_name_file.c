/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_name_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 10:30:28 by alex              #+#    #+#             */
/*   Updated: 2017/02/07 10:38:05 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * return a name file
 */
static int ft_fork_name_file_set_int_different(char *s, int i, int c)
{
  while (s[i])
  {
    if (s[i] != c)
    {
      break;
    }
    i++;
  }
  return (i);
}

static int ft_fork_name_file_set_int_equal(char *s, int i, int c)
{
  while (s[i])
  {
    if (s[i] == c)
    {
      break;
    }
    i++;
  }
  return (i);
}

char  *ft_fork_name_file(char **command, int i)
{
  int index;
  char *name_file;
  char *cmd;

  cmd = *command;
  name_file = NULL;
  i = ft_fork_name_file_set_int_different(cmd, i, SPACE_SEPARATOR);
  index = i;
  index = ft_fork_name_file_set_int_equal(cmd, index, SPACE_SEPARATOR);
  if (!(name_file = ft_strsub(cmd, i, index - i)))
  {
    return (NULL);
  }
  while (i < index)
  {
    cmd[i] = SPACE_SEPARATOR;
    i++;
  }
  return (name_file);
}
