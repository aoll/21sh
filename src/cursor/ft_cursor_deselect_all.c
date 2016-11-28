#include "project.h"

/**
 * cancel all reverse char marked after the index
 */
static int  ft_arr_cancel_reverse_video(t_arr *arr, int index, t_arr *select_line)
{
  unsigned char *s_line;

  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (index);
    s_line = *(unsigned char **)s_line;
    if (s_line[5] == 1)
    {
      s_line[5] = 0;
      free(ft_arr_pop(&select_line, select_line->length - 1));
    }
    index++;
  }
  return (EXIT_SUCCESS);
}

/**
 * deselect all char and clean the t_arr select_line
 * overide the line with a new line in basic video mode
 */
int  ft_cursor_deselect_all(t_cursor *cursor, t_arr *arr, t_arr *select_line)
{
  t_cursor tmp;

  if (!select_line->length || !cursor->save_cursor_position)
  {
    return (EXIT_SUCCESS);
  }
  tmp.index_line = cursor->index_line;
  tmp.pos_y = cursor->pos_y;
  tmp.pos_x = cursor->pos_x;
  ft_arr_cancel_reverse_video(arr, 0, select_line);
  ft_term_apply_cmd(cursor->save_cursor_position, 1);
  ft_cursor_home(cursor, arr);
  ft_term_apply_cmd(cursor->mode_insertion_end, 1);
  ft_arr_print(arr);
  ft_term_apply_cmd(cursor->restore_cursor_position, 1);
  ft_term_apply_cmd(cursor->mode_insertion, 1);
  cursor->index_line = tmp.index_line;
  cursor->pos_y = tmp.pos_y;
  cursor->pos_x = tmp.pos_x;

  return (EXIT_SUCCESS);
}
