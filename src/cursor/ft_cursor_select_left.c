#include "project.h"

/**
 * if is_will_reverse = 1
 * add to select_line four space and overide in reverse video the four space
 * present on the screen
 * or
 * if is_will_reverse = 0 pop and free to select_line four space and overide
 * the four space presenet on the screen in basic video mode
 */
static int  ft_cursor_select_overide_tab(t_cursor *cursor, t_arr *arr,
  t_arr *select_line, int is_will_reverse)
{
  int index_tab;
  unsigned char *s_line;

  index_tab = 0;
  while (index_tab < TABULATION_LEN)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (cursor->index_line + index_tab);
    s_line = *(unsigned char **)s_line;
    s_line[5] = is_will_reverse;
    if (is_will_reverse)
    {
      ft_arr_push(&select_line, ft_strdup((char *)s_line), 0);
    }
    else if (select_line->length)
    {
      free(ft_arr_pop(&select_line, select_line->length - 1));
    }
    ft_putstr((const char *)s_line);
    index_tab++;
  }
  return (EXIT_SUCCESS);
}

/**
 * if is_will_reverse = 1
 * add to select_line the char and overide in reverse video the char
 * present on the screen
 * or
 * if is_will_reverse = 0 pop and free to select_line a char and overide
 * the char present on the screen in basic video mode
 */
static int  ft_cursor_select_overide_char(t_cursor *cursor, t_arr *arr,
  t_arr *select_line, int is_will_reverse)
{
  unsigned char *s_line;

  s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (cursor->index_line);
  s_line = *(unsigned char **)s_line;
  ft_putstr((const char *)s_line);
  s_line[5] = is_will_reverse;
  if (is_will_reverse)
  {
    ft_arr_push(&select_line, ft_strdup((const char *)s_line), 0);
  }
  else
  {
    free(ft_arr_pop(&select_line, select_line->length - 1));
  }
  return (EXIT_SUCCESS);
}

/**
 * select the char left to the cursor
 */
int  ft_cursor_select_left(t_cursor *cursor, t_arr *arr, t_arr *select_line)
{
  unsigned char *s_line;
  int err;
  int is_will_reverse;

  is_will_reverse = 0;
  if ((err = ft_cursor_left(cursor, arr)))
  {
    return (EXIT_FAILURE);
  }
  ft_term_apply_cmd(cursor->save_cursor_position, 1);
  s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (cursor->index_line);
  s_line = *(unsigned char **)s_line;
  if (s_line[5] != 1)
  {
    is_will_reverse = 1;
    ft_term_apply_cmd(cursor->mode_reverse_video, 1);
  }
  ft_term_apply_cmd(cursor->mode_insertion_end, 1);
  if (s_line[4] == 1)
  {
    ft_cursor_select_overide_tab(cursor, arr, select_line, is_will_reverse);
  }
  else
  {
    ft_cursor_select_overide_char(cursor, arr, select_line, is_will_reverse);
  }
  ft_term_apply_cmd(cursor->mode_insertion, 1);
  ft_term_apply_cmd(cursor->mode_basic_video, 1);
  ft_term_apply_cmd(cursor->restore_cursor_position, 1);
  return (EXIT_SUCCESS);
}
