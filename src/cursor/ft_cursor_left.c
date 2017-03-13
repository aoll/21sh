/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 08:48:22 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 09:14:37 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/**
 * clear all the screen and restore the position of the cursor
 */
int  ft_cursor_clear_all_screen(t_cursor *cursor, int is_up)
{
  int pos_y;

  pos_y = 0;
  ft_term_apply_cmd(cursor->up, cursor->terminal_size.ws_row - 1);
  if (is_up)
  {
    ft_term_apply_cmd(cursor->down, cursor->terminal_size.ws_row - 1);
  }
  ft_cursor_move_x(0, cursor->move_x);
  while (pos_y < cursor->terminal_size.ws_row)
  {
    ft_term_apply_cmd(cursor->clear_current_line, 1);
    ft_term_apply_cmd(cursor->up, 1);
    pos_y++;
  }
  return (EXIT_SUCCESS);
}

/**
 * clear the actual line and reprint from line - 1 to line - 1
 */
int  ft_cursor_scroll_up(t_cursor *cursor, t_arr *arr)
{
  void *s_line;
  int index_start_showed;
  int len_tmp;
  int index_end_showed;

  cursor->y_start--;
  ft_cursor_clear_all_screen(cursor, 1);
  ft_cursor_move_x(0, cursor->move_x);
  s_line = arr->ptr;
  len_tmp = arr->length;
  index_start_showed = ft_index_line_start_showed(cursor, arr);
  index_end_showed = ft_cursor_index_prev_line_end(
    cursor, arr, index_start_showed);
  arr->length = index_end_showed + 1 - index_start_showed;
  if ((cursor->pos_y - 1) == 0)
    ft_putstr(cursor->prompt);
  arr->ptr = (unsigned char *)arr->ptr + arr->sizeof_elem * index_start_showed;
  ft_arr_print(arr);
  arr->length = len_tmp;
  arr->ptr = s_line;
  ft_term_apply_cmd(cursor->up, cursor->terminal_size.ws_row - 1);
  return (EXIT_SUCCESS);
}

static int  ft_cursor_left_up_line_set_cursor(
  t_cursor *cursor, t_arr *arr, unsigned char *s_line)
{
  if (s_line[4] == 1)
  {
    ft_cursor_left_tab(cursor, 1);
  }
  else if (*s_line == 10)
  {
    ft_cursor_left_chariot(cursor, arr);
  }
  else
  {
    cursor->index_line--;
  }
  return (EXIT_SUCCESS);
}
/**
 * if the cursor position is on the first col
 */
static int  ft_cursor_left_up_line(
  t_cursor *cursor, t_arr *arr, unsigned char *s_line)
{
  if (cursor->pos_y)
  {
    if (cursor->pos_y == cursor->y_start)
    {
      ft_cursor_scroll_up(cursor, arr);
    }
    else
    {
      ft_term_apply_cmd(cursor->up, 1);
    }
    cursor->pos_y--;
    cursor->pos_x = cursor->terminal_size.ws_col - 1;
    ft_cursor_move_x(cursor->pos_x, cursor->move_x);
    ft_cursor_left_up_line_set_cursor(cursor, arr, s_line);
  }
  return (EXIT_SUCCESS);
}

/**
 * move the cursor to current position - 1 on the same line or line - 1 if
 * actual position is 0
 */

int  ft_cursor_left(t_cursor *cursor, t_arr *arr)
{
  unsigned char *s_line;

  if ((cursor->index_line - 1) >= 0
  && cursor->left && cursor->up && cursor->move_x)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem *
    (cursor->index_line - 1);
    s_line = *(unsigned char **)s_line;
    if (cursor->pos_x)
    {
      ft_cursor_left_same_line(cursor, s_line);
    }
    else
    {
      ft_cursor_left_up_line(cursor, arr, s_line);
    }
  }
  return (EXIT_SUCCESS);
}
