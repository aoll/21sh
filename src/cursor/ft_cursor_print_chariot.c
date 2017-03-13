/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_print_chariot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:53:30 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 09:23:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int  ft_cursor_print_chariot_set_cursor(t_cursor *cursor)
{
  cursor->pos_x = 0;
  cursor->pos_y++;
  cursor->y_total++;
  ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  return (EXIT_SUCCESS);
}
/**
 * print a return chariot
 */
int  ft_cursor_print_chariot(t_cursor *cursor, t_arr *arr)
{
  unsigned char *s_line;
  int len_tmp;
  int index_start_showed;

  s_line = arr->ptr;
  len_tmp = arr->length;
  if (cursor->pos_y + 1 >= cursor->terminal_size.ws_row)
  {
    cursor->y_start++;
    ft_cursor_clear_up(cursor);
    index_start_showed = ft_arr_index_line_start_showed(
      cursor, arr, cursor->pos_y + 1 - cursor->terminal_size.ws_row + 1);
    arr->ptr = (unsigned char *)arr->ptr
    + arr->sizeof_elem * index_start_showed;
    arr->length -= (index_start_showed + 1);
    ft_arr_print(arr);
    arr->ptr = s_line;
    arr->length = len_tmp;
  }
  ft_putchar('\n');
  ft_cursor_print_chariot_set_cursor(cursor);
  return (EXIT_SUCCESS);
}
