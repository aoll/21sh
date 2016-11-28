#include "project.h"

/**
 * move the cursor to the start of the line, col 0 and raw 0 (before the prompt
 * not raw 0 of the screen) even if it is a multiple line
 */
int  ft_cursor_move_to_start(t_cursor *cursor, t_arr *arr)
{
  int err;

  if (!cursor)
  {
    return (EXIT_FAILURE);
  }
  if ((err = ft_cursor_home(cursor, arr))
  || (err = ft_term_apply_cmd(cursor->left, cursor->prompt_len)))
  {
    return (EXIT_FAILURE);
  }
  // cursor->pos_x = 0;
  return (EXIT_SUCCESS);
}
