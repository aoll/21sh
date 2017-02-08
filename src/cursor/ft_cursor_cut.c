#include "project.h"

/**
 * dup the selection in a new arr copy_line, and reprint the line without
 * the selection
 */
int  ft_cursor_cut(t_cursor *cursor, t_arr *arr, t_arr *select_line, t_arr **copy_line)
{
  int index;
  unsigned char *s_line;
  int nb_line_displayed;
  int index_line_tmp;

  index = 0;
  index_line_tmp = cursor->index_line;
  nb_line_displayed = ft_cursor_nb_line_displayed(cursor, arr, 0, 0);
  ft_cursor_end(cursor, arr);
  ft_cursor_clear_up(cursor);

  ft_cursor_copy_line(cursor, select_line, copy_line);
  while (select_line->length)
  {
    free(ft_arr_pop(select_line, 0));
  }
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * index;
    s_line = *(unsigned char **)s_line;
    if (s_line[5] == 1)
    {
      free(ft_arr_pop(arr, index));
    }
    else
    {
      index++;
    }
  }
  if (index_line_tmp > (int)arr->length)
  {
    index_line_tmp = arr->length;
  }
  cursor->index_line = arr->length;

  nb_line_displayed = ft_cursor_nb_line_displayed(cursor, arr, 0, 0);
  ft_putstr(cursor->prompt);
  ft_arr_print(arr);
  ft_cursor_restore_y_x(cursor, arr, nb_line_displayed);
  ft_cursor_restore_index(cursor, arr, index_line_tmp);
  return (EXIT_SUCCESS);
}
