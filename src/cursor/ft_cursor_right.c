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
 * the current position of the cursor is the last col, the next char is one
 * down line
 */
static int  ft_cursor_right_down_line(t_cursor *cursor, unsigned char *s_line)
{
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
      ft_cursor_right_down_line(cursor, s_line);
    }
  }
  return (EXIT_SUCCESS);
}
