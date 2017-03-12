/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_print_overide_line.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:54:50 by alex              #+#    #+#             */
/*   Updated: 2017/03/12 17:55:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/**
 * print from the cursor of the line and overide the old line
 */
int  ft_cursor_print_overide_line(t_cursor *cursor, t_arr *arr)
{
  t_arr tmp;
  int y_new;

  ft_term_apply_cmd(cursor->mode_insertion_end, 1);
  tmp.length = arr->length - (cursor->index_line);
  tmp.ptr = (unsigned char *)arr->ptr + cursor->index_line * arr->sizeof_elem;
  tmp.f_print = arr->f_print;
  tmp.sizeof_elem = arr->sizeof_elem;
  ft_arr_print(&tmp);
  if (!((cursor->prompt_len + arr->length) % cursor->terminal_size.ws_col))
  {
    ft_putchar('Z');
    ft_term_apply_cmd(cursor->left, 1);
    ft_term_apply_cmd(cursor->sup_char, 1);
  }
  y_new = (cursor->prompt_len + arr->length) / cursor->terminal_size.ws_col;
  ft_term_apply_cmd(cursor->up, y_new - cursor->pos_y);
  ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  return (EXIT_SUCCESS);
}
