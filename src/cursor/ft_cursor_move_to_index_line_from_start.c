#include "project.h"

/**
 * move the cursor to index_line position from start position
 */
int  ft_cursor_move_to_index_line_from_start(t_cursor *cursor)
{
  if (!cursor)
  {
    return (EXIT_FAILURE);
  }
  cursor->pos_x = (cursor->index_line + cursor->prompt_len) %
  cursor->terminal_size.ws_col;
  cursor->pos_y = (cursor->index_line + cursor->prompt_len) /
  cursor->terminal_size.ws_col;
  ft_term_apply_cmd(cursor->down, cursor->pos_y);
  ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  return (EXIT_SUCCESS);
}
