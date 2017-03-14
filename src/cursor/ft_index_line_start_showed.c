/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_line_start_showed.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:39:58 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 10:40:47 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/*
 * return the index of the first char print with line + 1
 * from the index in parameter
 * this function calcul the number of char can be dysplayed
 */
int  ft_index_line_start_showed(t_cursor *cursor, t_arr *arr)
{
  unsigned char *s_line;
  int index_line;
  int nb_line;
  int index;

  nb_line = 0;
  index = 0;
  index_line = cursor->prompt_len;
  while (index < (int)arr->length)
  {
    if (nb_line == cursor->y_start)
      return (index);
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * index;
    s_line = *(unsigned char **)s_line;
    if (index_line == cursor->terminal_size.ws_col - 1 || *s_line == 10)
    {
      nb_line++;
      index_line = -1;
    }
    index++;
    index_line++;
  }
  return (index);
}
