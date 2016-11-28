#include "project.h"

/**
 * move the cursor of the begin of the line even if it's a multiple line
 */
int  ft_cursor_home(t_cursor *cursor, t_arr *arr)
{
  if (!cursor->up || !cursor->move_x)
  {
    return (EXIT_FAILURE);
  }
  while (cursor->index_line)
  {
    ft_cursor_left(cursor, arr);
  }
  // ft_term_apply_cmd(cursor->up, cursor->pos_y);
  // cursor->pos_y = 0;
  // cursor->index_line = 0;
  // cursor->prev_chariot = 0;
  // cursor->pos_x = cursor->prompt_len;
  // ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  return (EXIT_SUCCESS);
}
