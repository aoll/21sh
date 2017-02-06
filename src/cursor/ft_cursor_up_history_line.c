#include "project.h"

/**
 * clear the current line and reprint the command - 1
 */
int  ft_cursor_up_history_line(t_cursor *cursor, t_arr *history_line, t_arr **current_line, t_arr **arr)
{
  t_arr *tmp_arr;
  t_arr *tmp_current_line;

  tmp_arr = *arr;
  tmp_current_line = *current_line;
  ft_cusor_clear_down_line(cursor, tmp_arr);
  cursor->index_line = 0;
  cursor->pos_x = cursor->prompt_len;
  cursor->pos_y = 0;
  cursor->y_total = 1;
  cursor->prev_chariot = 0;
  cursor->chariot = 0;
  cursor->y_start = 0;
  cursor->index_history--;
  tmp_current_line = *(t_arr **)((unsigned char *)history_line->ptr + cursor->index_history * history_line->sizeof_elem);
  if (tmp_current_line->length == 2)
  {
    tmp_arr = *(t_arr **)((unsigned char *)tmp_current_line->ptr + tmp_current_line->sizeof_elem);
  }
  else
  {
    tmp_arr = *(t_arr **)((unsigned char *)tmp_current_line->ptr);
  }
  // tmp_arr->f_print = &ft_arr_putchar;

  ft_arr_print(tmp_arr);
  cursor->index_line = tmp_arr->length;

  ft_cursor_restore_y_x(cursor, tmp_arr, ft_cursor_nb_line_displayed(cursor, tmp_arr, 0, 0));

  ft_cursor_restore_index(cursor, tmp_arr, cursor->index_line);
  *arr = tmp_arr;
  *current_line = tmp_current_line;
  return (EXIT_SUCCESS);
}
