/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_restore_y_x.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:36:12 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 09:46:22 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int  ft_cursor_restore_y_x_set_cursor(
  t_cursor *cursor, unsigned char *s_line, int *index)
{
  if (cursor->pos_x == cursor->terminal_size.ws_col - 1 || *s_line == 10)
  {
    cursor->pos_y++;
    cursor->pos_x = 0;
    (*index)++;
  }
  else
  {
    cursor->pos_x++;
    (*index)++;
  }
  return (EXIT_SUCCESS);
}
/*
 * restore the pos_y and pos_y of the cursor
 */
int  ft_cursor_restore_y_x(t_cursor *cursor, t_arr *arr, int nb_line_displayed)
{
  int index;
  unsigned char *s_line;

  index = 0;
  cursor->pos_y = 0;
  cursor->pos_x = cursor->prompt_len;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + index * arr->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    if (index == cursor->index_line)
    {
      cursor->y_start = cursor->pos_y - (nb_line_displayed - 1);
      return (EXIT_SUCCESS);
    }
    ft_cursor_restore_y_x_set_cursor(cursor, s_line, &index);
  }
  cursor->y_start = cursor->pos_y - (nb_line_displayed - 1);
  return (EXIT_SUCCESS);
}
