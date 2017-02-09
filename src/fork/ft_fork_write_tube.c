/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_write_tube.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 08:16:30 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 08:23:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * read a file to write on a other
 * return the len read
 */
int  ft_fork_write_tube(int dst_fd, int src_fd)
{
  int rd;
  int len;
  char *buff;

  len = 0;
  buff = ft_strnew(1);
  while ((rd = read(src_fd, buff, 1)))
  {
    if (rd < 0)
      break;
    write(dst_fd, buff, 1);
    len++;
  }
  ft_str_free(&buff);
  return (len);
}
