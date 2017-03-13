/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:47:13 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 11:31:49 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int  ft_cursor_right_down_line_set_cursor(t_cursor *cursor)
{
  ft_term_apply_cmd(cursor->down, 1);
  cursor->pos_y++;
  cursor->pos_x = 0;
  ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  cursor->index_line++;
  return (EXIT_SUCCESS);
}
/**
 * the current position of the cursor is the last col, the next char is one
 * down line
 */
static int  ft_cursor_right_down_line(
  t_cursor *cursor, t_arr *arr, unsigned char *s_line)
{
  int pos_y_screen;

  pos_y_screen = ft_cursor_y_screen(cursor, arr);
  if (pos_y_screen == cursor->terminal_size.ws_row - 1)
    ft_cursor_right_line_more(cursor, arr);
  if (s_line[4] == 1)
  {
    if (cursor->pos_x + 1 == cursor->terminal_size.ws_col)
      ft_cursor_right_down_line_set_cursor(cursor);
    ft_cursor_right_tab(cursor, 1);
  }
  else if (*s_line == 10)
  {
    ft_cursor_right_chariot(cursor);
  }
  else
  {
    ft_cursor_right_down_line_set_cursor(cursor);
  }
  return (EXIT_SUCCESS);
}
/**
 * move the cursor to current position + 1 on the same line or line + 1 if
 * actual position is col max
 */
int  ft_cursor_right(t_cursor *cursor, t_arr *arr)
{
  unsigned char *s_line;

  if (cursor->index_line + 1 <= (int)arr->length
  && cursor->right && cursor->down && cursor->move_x)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (cursor->index_line);
    s_line = *(unsigned char **)s_line;
    if (cursor->pos_x + 1 < cursor->terminal_size.ws_col && *s_line != 10)
    {
      ft_cursor_right_same_line(cursor, arr, s_line);
    }
    else
    {
      ft_cursor_right_down_line(cursor, arr, s_line);
    }
  }
  return (EXIT_SUCCESS);
}
