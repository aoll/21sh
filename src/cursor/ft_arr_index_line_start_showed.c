/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_index_line_start_showed.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:17:05 by alex              #+#    #+#             */
/*   Updated: 2017/03/12 17:24:44 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/*
** return the index to start the arr with show n - line_off line
*/
int  ft_arr_index_line_start_showed(t_cursor *cursor, t_arr *arr, int line_off)
{
  int index;
  int line;
  int index_line;
  char *s_line;

  index_line = cursor->prompt_len;
  index = -1;
  line = 0;
  while (++index < (int)arr->length)
  {
    s_line = *(char **)((unsigned char *)arr->ptr + arr->sizeof_elem * index);
    if (line >= line_off)
    {
      return (index);
    }
    else if (index_line == cursor->terminal_size.ws_col - 1 || *s_line == 10)
    {
      index_line = -1;
      line++;
    }
    index_line++;
  }
  return (index);
}
