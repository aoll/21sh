#include "project.h"

/**
 *
 */
int  ft_check_is_char(t_arr *arr, char c)
{
  int i;
  char *s_line;
  int nb;

  i = 0;
  nb = 0;
  while (i < (int)arr->length)
  {
    s_line = *(char **)((unsigned char *)arr->ptr + i * arr->sizeof_elem);
    if (*s_line == c)
    {
      nb++;
    }
    i++;
  }
  if (nb)
  {
    return (nb % 2);
  }
  return (EXIT_SUCCESS);
}

/**
 * pop a elem to arr and four elem if the elem at the index in parameter is
 * marked like a tab
 * is_prev_char is equal to 1 if is the elem before, 0 if is the pointed by the
 * the index is targeted
 * return the new index
 */
static int  ft_cursor_arr_pop_elem(t_arr *arr, t_cursor *cursor,
  int index_line_tmp, int is_prev_char)
{
  unsigned char *s_line;
  int index_tab;
  void *s;

  s_line = (unsigned char *)arr->ptr + arr->sizeof_elem *
  (index_line_tmp - is_prev_char);
  s_line = *(unsigned char **)s_line;
  if (*s_line == '"')
  {
    if (!cursor->quote)
    {
      cursor->dquote = !cursor->dquote;
      if (ft_check_is_char(arr, '\''))
      {
        cursor->dquote = false;
        cursor->quote = true;
      }
    }
  }
  if (*s_line == '\'')
  {
    if (!cursor->dquote)
    {
      cursor->quote = !cursor->quote;
      if (ft_check_is_char(arr, '"'))
      {
        cursor->quote = false;
        cursor->dquote = true;
      }
    }
  }
  if (s_line[4] == 1)
  {
    index_tab = -1;
    while (++index_tab < TABULATION_LEN)
    {
      if ((s = ft_arr_pop(&arr, (index_line_tmp -= is_prev_char))))
        free(s);
    }
  }
  else
  {
    if (*s_line == 10)
    {
      cursor->chariot--;
      if (is_prev_char)
      {
        cursor->prev_chariot--;
      }
    }
    if ((s = ft_arr_pop(&arr, (index_line_tmp -= is_prev_char))))
      free(s);
  }
  return (index_line_tmp);
}

/**
 * delete the prev char if is_prev_char is equal to 1
 * delete the actual char if is_prev_char is equal to 0
 */
int  ft_cursor_del_or_suppr(t_cursor *cursor, t_arr *arr, int is_prev_char)
{
  int index_line_tmp;
  int y_tmp;
  int x_tmp;
  int chariot_tmp;
  int err;

  if (is_prev_char)
  {
    ft_cursor_left(cursor, arr);
  }
  is_prev_char = 0;
  ft_term_apply_cmd(cursor->save_cursor_position, 1);
  index_line_tmp = cursor->index_line;
  y_tmp = cursor->pos_y;
  x_tmp = cursor->pos_x;
  chariot_tmp = cursor->chariot;
  if (!cursor || (cursor->index_line - is_prev_char) < 0 ||
  !cursor->clear_down || !cursor->left)
  {
    return (EXIT_FAILURE);
  }
  if ((err = ft_cursor_move_to_start(cursor, arr))
  || (err = ft_term_apply_cmd(cursor->clear_down, 1)))
  {
    return (EXIT_FAILURE);
  }
  index_line_tmp = ft_cursor_arr_pop_elem(arr, cursor, index_line_tmp, is_prev_char);
  ft_restore_prompt_and_line(cursor, arr);
  cursor->index_line = index_line_tmp;
  cursor->pos_x = x_tmp;
  cursor->pos_y = y_tmp;
  ft_term_apply_cmd(cursor->restore_cursor_position, 1);
  return (EXIT_SUCCESS);
}
