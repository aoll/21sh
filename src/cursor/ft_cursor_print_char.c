/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_print_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:36:29 by alex              #+#    #+#             */
/*   Updated: 2017/03/12 17:50:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/*
 *
 */
static int  ft_cursor_print_char_new_line(t_cursor *cursor)
{
  ft_putchar('Z');
  ft_term_apply_cmd(cursor->left, 1);
  ft_term_apply_cmd(cursor->sup_char, 1);
  cursor->pos_x = 0;
  cursor->pos_y++;
  cursor->y_total++;
  return (EXIT_SUCCESS);
}
/*
 *
 */
static int  ft_cursor_print_char_process(
  t_cursor *cursor, t_arr *arr, unsigned char *s_line, int len_tmp)
{
  int index_start_showed;

  cursor->y_start++;
  ft_cursor_clear_up(cursor);
  index_start_showed = ft_arr_index_line_start_showed(
    cursor, arr, cursor->pos_y + 1 - cursor->terminal_size.ws_row + 1);
  arr->ptr = (unsigned char *)arr->ptr + arr->sizeof_elem * index_start_showed;
  arr->length -= (index_start_showed + 1);
  ft_arr_print(arr);
  arr->ptr = s_line;
  arr->length = len_tmp;
  return (EXIT_SUCCESS);
}
/*
 * print a char
 */
int  ft_cursor_print_char(t_cursor *cursor, char c, t_arr *arr)
{
  unsigned char *s_line;
  int len_tmp;

  s_line = arr->ptr;
  len_tmp = arr->length;
  if (cursor->pos_y + 1 >= cursor->terminal_size.ws_row
    && cursor->pos_x + 1 >= cursor->terminal_size.ws_col)
  {
    ft_cursor_print_char_process(cursor, arr, s_line, len_tmp);
  }
  ft_putchar(c);
  cursor->pos_x++;
  if (cursor->pos_x >= cursor->terminal_size.ws_col)
  {
    ft_cursor_print_char_new_line(cursor);
  }
  return (EXIT_SUCCESS);
}
