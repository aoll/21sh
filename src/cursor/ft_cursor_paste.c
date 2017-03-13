/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_paste.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:16:16 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 09:19:28 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int  ft_cursor_paste_switch(t_cursor *cursor, t_arr *arr, char *s_line)
{
  if (cursor->pos_x >= cursor->terminal_size.ws_col || *s_line == 10)
  {
    if (cursor->index_line == (int)arr->length)
    {
      ft_putchar('Z');
      ft_term_apply_cmd(cursor->left, 1);
      ft_term_apply_cmd(cursor->sup_char, 1);
    }
    cursor->pos_x = 0;
    cursor->pos_y++;
  }
  if ((cursor->pos_y - cursor->y_start) == cursor->terminal_size.ws_row)
  {
    cursor->y_start++;
  }
  return (EXIT_SUCCESS);
}
/**
 * print the arr (copy_line) and push in the arr (current line) the elements
 */
int  ft_cursor_paste(t_cursor *cursor, t_arr *arr, t_arr *copy_line)
{
  int index;
  char *s_line;

  ft_term_apply_cmd(cursor->mode_insertion, 1);
  ft_arr_print(copy_line);
  index = 0;
  while (index < (int)copy_line->length)
  {
    s_line = *(char **)(
      (unsigned char*)copy_line->ptr + index * copy_line->sizeof_elem);
    ft_arr_push(arr, ft_strdup(s_line), cursor->index_line);
    index++;
    cursor->index_line++;
    cursor->pos_x++;
    ft_cursor_paste_switch(cursor, arr, s_line);
  }
  return (EXIT_SUCCESS);
}
