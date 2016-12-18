#include "project.h"

/**
 * move x_time the cursor tho the left side
 */
int  ft_cursor_mvt_left(t_cursor *cursor, t_arr *arr, int mvt_x)
{
  while (cursor->index_line && mvt_x)
  {
    ft_cursor_left(cursor , arr);
    mvt_x--;
  }
  return (EXIT_SUCCESS);
}


/**
 * if it's possible move the cursor to a position line - 1
 */
int  ft_cursor_up_line(t_cursor *cursor, t_arr *arr)
{
  int pos_y_old;
  int pos_x_old;
  int mvt_x;

  if (!cursor->pos_y)
  {
    return (EXIT_SUCCESS);
  }
  pos_y_old = cursor->pos_y;
  pos_x_old = cursor->pos_x;
  mvt_x = cursor->pos_x;
  mvt_x++;
  ft_cursor_mvt_left(cursor, arr, mvt_x);
  mvt_x = cursor->pos_x;
  ft_cursor_mvt_left(cursor, arr, mvt_x);
  mvt_x = 0;
  if (!cursor->pos_y)
  {
    mvt_x = cursor->prompt_len;
  }
  while (cursor->index_line < (int)arr->length && mvt_x < pos_x_old)
  {
    ft_cursor_right(cursor, arr);
    mvt_x++;
    if (cursor->pos_y == pos_y_old)
    {
      ft_cursor_left(cursor, arr);
      break;
    }
  }

  return (EXIT_SUCCESS);
}
