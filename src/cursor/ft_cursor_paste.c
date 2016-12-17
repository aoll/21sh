#include "project.h"

/**
 * print the arr (copy_line) and push in the arr (current line) the elements
 */
int  ft_cursor_paste(t_cursor *cursor, t_arr *arr, t_arr *copy_line)
{
  int index;
  unsigned char *s_line;

  // ft_mode_insertion();
  ft_term_apply_cmd(cursor->mode_insertion, 1);
  ft_arr_print(copy_line);
  index = 0;
  while (index < (int)copy_line->length)
  {
    s_line = (unsigned char*)copy_line->ptr + index * copy_line->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    ft_arr_push(&arr, ft_strdup((char *)s_line), cursor->index_line);
    index++;
    cursor->index_line++;
    cursor->pos_x++;
    if (cursor->pos_x >= cursor->terminal_size.ws_col || *s_line == 10)
    {
      cursor->pos_x = 0;
      cursor->pos_y++;
    }
    if ((cursor->pos_y - cursor->y_start) == cursor->terminal_size.ws_row)
    {
      cursor->y_start++;
    }
  }
  return (EXIT_SUCCESS);
}
