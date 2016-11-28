#include "project.h"

/**
 * move the cursor to end of the line even if it's a multi-ligne
 */
int  ft_cursor_end(t_cursor *cursor, t_arr *arr)
{
  // int y_all;

  while (cursor->index_line != (int)arr->length)
  {
    ft_cursor_right(cursor, arr);
  }
  // if (!cursor->down || !cursor->move_x)
  // {
  //   return (EXIT_FAILURE);
  // }
  // y_all = (arr->length + cursor->prompt_len) / cursor->terminal_size.ws_col;
  // ft_term_apply_cmd(cursor->down, y_all - cursor->pos_y);
  // cursor->pos_y = y_all;
  // cursor->pos_x = (arr->length + cursor->prompt_len) % cursor->terminal_size.ws_col;
  // ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  // cursor->index_line = arr->length;// - 1;
  return (EXIT_SUCCESS);
}
