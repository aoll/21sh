#include "project.h"

/**
 * if the next char is a tabulation, the cursor must move the TABULATION_LEN
 * if the the first space is on the same line than the cursor before mouve
 * same_line = 0 else same_line = 1
 */
static int  ft_cursor_right_tab(t_cursor *cursor, int same_line)
{
  int index_tab;

  index_tab = 0;
  index_tab += same_line;
  while (index_tab < TABULATION_LEN)
  {
    ft_term_apply_cmd(cursor->right, 1);
    cursor->pos_x++;
    cursor->index_line++;
    index_tab++;
    if (cursor->pos_x + 1 == cursor->terminal_size.ws_col && index_tab < TABULATION_LEN)
    {
      cursor->pos_y++;
      ft_term_apply_cmd(cursor->down, 1);
      cursor->pos_x = 0;
      ft_cursor_move_x(cursor->pos_x, cursor->move_x);
      index_tab++;
      cursor->index_line++;
    }
  }
  return (EXIT_SUCCESS);
}

/**
 * next char is on the same line as the cursor
 */
static int  ft_cursor_right_same_line(t_cursor *cursor, t_arr *arr,
  unsigned char *s_line)
{
  if (cursor->index_line + 1 == (int)arr->length)
  {
    ft_term_apply_cmd(cursor->right, 1);
    cursor->pos_x++;
    cursor->index_line++;
  }
  else
  {
    if (s_line[4] == 1)
    {
      ft_cursor_right_tab(cursor, 0);
    }
    else
    {
      ft_term_apply_cmd(cursor->right, 1);
      cursor->pos_x++;
      cursor->index_line++;
    }
  }
  return (EXIT_SUCCESS);
}

/**
 * clear the screen from the bottom line
 */
int  ft_clear_up_from_bottom(t_cursor *cursor)
{
  int i;

  // ft_term_apply_cmd(cursor->save_cursor_position, 1);
  i = 0;
  ft_cursor_move_x(0, cursor->move_x);
  while (i < cursor->terminal_size.ws_row)
  {
    ft_term_apply_cmd(cursor->clear_current_line, 1);
    ft_term_apply_cmd(cursor->up, 1);
    i++;
  }
  // ft_term_apply_cmd(cursor->restore_cursor_position, 1);
  return (EXIT_SUCCESS);
}

/**
 * return the index of the last char print with line + 1
 */
int  ft_index_line_end_showed(t_cursor *cursor, t_arr *arr)
{
  int index;
  unsigned char *s_line;
  int index_line;

  index = cursor->index_line + 1; // not sure
  index_line = 0;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * index;
    s_line = *(unsigned char **)s_line;
    if (index_line == cursor->terminal_size.ws_col - 1 || *s_line == 10)
    {
      if (*s_line == 10)
      {
        return (index - 1);
      }
      return (index);
    }
    index_line++;
    index++;
  }
  return (index);
}

/**
 * return the index of the first char print with line + 1
 * from the index in parameter
 * this function calcul the number of char can be dysplayed
 */
int  ft_index_line_start_showed(t_cursor *cursor, t_arr *arr, int index_end_showed)
{
  unsigned char *s_line;
  int index_line;
  int nb_line;

  index_line = 0;
  nb_line = 0;
  while (index_end_showed)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * index_end_showed;
    s_line = *(unsigned char **)s_line;
    if (index_line == cursor->terminal_size.ws_col - 1)
    {
      nb_line++;
      index_line = 0;
    }
    else
    {
      index_end_showed--;
      index_line++;
    }
    if (nb_line == cursor->terminal_size.ws_row - 1)
    {
      return (index_end_showed);
    }

  }
  return (index_end_showed);
}

/**
 * clean the screen
 * print the command with line + 1
 */
int  ft_cursor_right_line_more(t_cursor *cursor, t_arr *arr)
{
  int index_start_showed;
  int index_end_showed;
  void *ptr_tmp;
  int len_tmp;

  cursor->y_start++;
  ft_term_apply_cmd(cursor->save_cursor_position, 1);
  ft_clear_up_from_bottom(cursor);
  len_tmp = arr->length;
  ptr_tmp = arr->ptr;
  index_end_showed = ft_index_line_end_showed(cursor, arr);
  // ft_putstr("index_end_showed: ");ft_putnbr(index_end_showed);ft_putstr("\n");
  index_start_showed = ft_index_line_start_showed(cursor, arr, cursor->index_line);// - 1);
  // ft_putstr("index_start_showed: ");ft_putnbr(index_start_showed);ft_putstr("\n");
  arr->ptr = (unsigned char *)arr->ptr + arr->sizeof_elem * index_start_showed;
  arr->length = cursor->index_line + 1 - index_start_showed;// + 1;
  // arr->length = index_end_showed - index_start_showed + 1;


  // if (cursor->index_line + 1 == len_tmp)
  // {
  //   arr->length--;
  // }
  ft_arr_print(arr);
  arr->ptr = (unsigned char *)arr->ptr + arr->sizeof_elem * cursor->index_line + 1;
  arr->length = len_tmp - index_end_showed - cursor->index_line - 1;
  ft_arr_print(arr);
  arr->length = len_tmp;
  arr->ptr = ptr_tmp;
  return (0);
  return (EXIT_SUCCESS);
}

/**
 * the current position of the cursor is the last col, the next char is one
 * down line
 */
static int  ft_cursor_right_down_line(t_cursor *cursor, t_arr *arr, unsigned char *s_line)
{
  if (cursor->pos_y + 1 >= cursor->terminal_size.ws_row)
  {
    ft_cursor_right_line_more(cursor, arr);
  }
  if (s_line[4] == 1)
  {
    if (cursor->pos_x + 1 == cursor->terminal_size.ws_col)
    {
      ft_term_apply_cmd(cursor->down, 1);
      cursor->pos_y++;
      cursor->pos_x = 0;
      ft_cursor_move_x(cursor->pos_x, cursor->move_x);
      cursor->index_line++;
    }
    ft_cursor_right_tab(cursor, 1);
  }
  else
  {
    ft_term_apply_cmd(cursor->down, 1);
    cursor->pos_y++;
    cursor->pos_x = 0;
    ft_cursor_move_x(cursor->pos_x, cursor->move_x);
    cursor->index_line++;
  }
  return (EXIT_SUCCESS);
}

/**
 * cursor is actually on a '\n' move down one time and place the cursor and the
 * first col
 */
int  ft_cursor_right_chariot(t_cursor *cursor)
{
  cursor->prev_chariot++;
  cursor->pos_y++;
  cursor->pos_x = 0;
  cursor->index_line++;
  ft_term_apply_cmd(cursor->down, 1);
  ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  return (EXIT_SUCCESS);
}

/**
 * move the cursor to current position + 1 on the same line or line + 1 if
 * actual position is col max
 */
int  ft_cursor_right(t_cursor *cursor, t_arr *arr)
{
  unsigned char *s_line;

  if (cursor->index_line + 1 <= (int)arr->length
  && cursor->right && cursor->down && cursor->move_x)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (cursor->index_line);
    s_line = *(unsigned char **)s_line;
    if (*s_line == 10)
    {
      ft_cursor_right_chariot(cursor);
    }
    else if (cursor->pos_x + 1 < cursor->terminal_size.ws_col)
    {
      ft_cursor_right_same_line(cursor, arr, s_line);
    }
    else
    {
      ft_cursor_right_down_line(cursor, arr, s_line);
    }
  }
  return (EXIT_SUCCESS);
}
