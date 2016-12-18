#include "project.h"

/**
 * if it's possible move the cursor to a position line + 1
 */
int  ft_cursor_down_line(t_cursor *cursor, t_arr *arr)
{
  int pos_y_old;
  int pos_x_old;
  int mvt_x;

  if (cursor->pos_y == cursor->y_total - 1)
  {
    return (EXIT_SUCCESS); //not sure!!
  }
  pos_y_old = cursor->pos_y;
  pos_x_old = cursor->pos_x;
  mvt_x = cursor->pos_x;
  while (cursor->index_line < (int)arr->length)
  {
    ft_cursor_right(cursor, arr);
    if (cursor->pos_y == pos_y_old + 1)
    {
      break;
    }
  }
  while (cursor->index_line < (int)arr->length && mvt_x)
  {
    ft_cursor_right(cursor, arr);
    if (cursor->pos_y >= pos_y_old + 2)
    {
      ft_cursor_left(cursor, arr);
      break;
    }
    mvt_x--;
  }

  return (EXIT_SUCCESS);
}
