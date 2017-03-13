/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_index_prev_line_end.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:02:25 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 09:09:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int  ft_cursor_index_prev_line_end_init(
  t_cursor *cursor, int *index_line, int *y_line)
{
  *index_line = 0;
  if (cursor->pos_y - 1 == 0)
    *index_line = cursor->prompt_len;
  *y_line = 0;
  return (EXIT_SUCCESS);
}
/**
 * return the index to the last line showed - 1
 */
int  ft_cursor_index_prev_line_end(t_cursor *cursor, t_arr *arr, int start)
{
  char *s_line;
  int index_line;
  int y_line;
  int arr_len;

  ft_cursor_index_prev_line_end_init(cursor, &index_line, &y_line);
  arr_len = (int)arr->length;
  while (start < arr_len)
  {
    if (y_line == cursor->terminal_size.ws_row)
      return (start - 1);
    s_line = *(char **)((unsigned char *)arr->ptr + arr->sizeof_elem * start);
    if (index_line == cursor->terminal_size.ws_col - 1 || *s_line == 10 )
    {
      index_line = -1;
      y_line++;
      if (y_line == cursor->terminal_size.ws_row && *s_line == 10)
        return (start - 1);
    }
    index_line++;
    start++;
  }
  return (start - 1);
}
