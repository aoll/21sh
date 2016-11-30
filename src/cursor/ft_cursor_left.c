#include "project.h"
// /**
//  * move the cursor to a actual position x - 1 (left)
//  */
//
int  ft_move_left_bw(void)
{
  char *cmd;
  // char *cmd2;
  // char *cmd3;


  // if ((cmd2 = tgetstr("ho", NULL)) == NULL) //move to the left
  //   ft_putstr("NULLLLLLLLLLLL\n");
    // return (EXIT_FAILURE); //pas quiter le programme

  // tputs(cmd2, 0, &my_putchar);
  if ((cmd = tgetstr("cs", NULL)) == NULL) //move to the left
    ft_putstr("NULLLLLLLLLLLL\n");
    // return (EXIT_FAILURE); //pas quiter le programme

    // return (EXIT_FAILURE); //pas quiter le programme
tputs(tgoto(cmd, 0, 1), 0, &my_putchar);
  // tputs(cmd, 0, &my_putchar);
  return (EXIT_SUCCESS);
}


/**
 * if the prev char is a tabulation, the cursor must move the TABULATION_LEN
 * if the the first space is on the same line than the cursor before mouve
 * same_line = 0 else same_line = 1
 */
static int  ft_cursor_left_tab(t_cursor *cursor, int same_line)
{
  int index_tab;

  index_tab = 0;
  cursor->index_line -= same_line;
  while (index_tab < TABULATION_LEN - same_line)
  {
    cursor->pos_x--;
    ft_term_apply_cmd(cursor->left, 1);
    cursor->index_line--;
    index_tab++;
    if (!cursor->pos_x && cursor->pos_y && index_tab < TABULATION_LEN)
    {
      ft_term_apply_cmd(cursor->up, 1);
      cursor->pos_y--;
      cursor->pos_x = cursor->terminal_size.ws_col - 1;
      ft_cursor_move_x(cursor->pos_x, cursor->move_x);
      cursor->index_line--;
      index_tab++;
    }
  }
  return (EXIT_SUCCESS);
}

/**
 * if the cursor postion is not on the first col
 */

static int  ft_cursor_left_same_line(t_cursor *cursor, unsigned char *s_line)
{
  if (s_line[4] == 1)
  {
    ft_cursor_left_tab(cursor, 0);
  }
  else
  {
    ft_term_apply_cmd(cursor->left, 1);
    cursor->pos_x--;
    cursor->index_line--;
  }
  return (EXIT_SUCCESS);
}

/**
 * nombre de char between two '\n' from the index in parameter to the first '\n'
 * founded or the begin of the line
 */
int  ft_nb_char_between_two_chariot(t_arr *arr, int index)
{
  int nb_char;
  unsigned char *s_line;

  nb_char = 0;
  while (index >= 0)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (index);
    s_line = *(unsigned char **)s_line;
    if (*s_line == 10)
    {
      return (nb_char);
    }
    nb_char++;
    index--;
  }

  return (nb_char);
}

/**
 * the cursor is on the last col after a return chariot
 * il will be just after the char on the return chariot
 */
int  ft_cursor_left_chariot(t_cursor *cursor, t_arr *arr)
{
  int nb_char;

  cursor->prev_chariot--;
  cursor->index_line--;
  if (cursor->prev_chariot)
  {
    nb_char = ft_nb_char_between_two_chariot(arr, cursor->index_line - 1);
    // ft_putnbr(nb_char);
    if (nb_char > cursor->terminal_size.ws_col)
    {
      nb_char = nb_char % cursor->terminal_size.ws_col;
    }
    if (!cursor->pos_y)
    {
      nb_char += cursor->prompt_len;
    }
  }
  else
  {
    nb_char = (cursor->prompt_len + cursor->index_line) % cursor->terminal_size.ws_col;
  }
  cursor->pos_x = nb_char;
  ft_cursor_move_x(cursor->pos_x, cursor->move_x);

  return (EXIT_SUCCESS);
}

/**
 * return the index of the start of the prev line
 */
int  ft_cursor_index_prev_line_start(t_cursor *cursor, t_arr *arr)
{
  int index;
  unsigned char *s_line;
  int index_line;
  bool is_one_prev_chariot;

  index = cursor->index_line - 1;
  index_line = 0;
  is_one_prev_chariot = false;
  while (index > 0)
  {
      s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * index;
      s_line = *(unsigned char **)s_line;
      if (index_line == cursor->terminal_size.ws_col - 1)
      {
        return (index);
      }
      if (*s_line == 10)
      {
        if (is_one_prev_chariot)
        {
          return (index + 1);
        }
        is_one_prev_chariot = true;
        index--;
      }
      index--;
      index_line++;
  }
  return (index);
}

/**
 * return the index to the last line showed - 1
 */
int  ft_cursor_index_prev_line_end(t_cursor *cursor, t_arr *arr, int start)
{
  unsigned char *s_line;
  int index_line;
  int y_line;
  int arr_len;

  index_line = 0;
  if (cursor->pos_y - 1 == 0)
  {
    index_line = cursor->prompt_len;
  }
  y_line = 0;
  arr_len = (int)arr->length;
  while (start < arr_len)
  {
    if (y_line == cursor->terminal_size.ws_row)
    {
      return (start - 1);
    }
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * start;
    s_line = *(unsigned char **)s_line;
    if (index_line == cursor->terminal_size.ws_col - 1 || *s_line == 10 )
    {
      index_line = 0;
      y_line++;
      if (y_line == cursor->terminal_size.ws_row && *s_line == 10)
      {
        return (start - 1);
      }
      start++;
    }
    else
    {
      start++;
      index_line++;
    }
  }
  return (start - 1);
}

/**
 * clear all the screen and restore the position of the cursor
 */
int  ft_cursor_clear_all_screen(t_cursor *cursor)
{
  int pos_y;

  pos_y = 0;
  // ft_term_apply_cmd(cursor->save_cursor_position, 1);
  ft_term_apply_cmd(cursor->down, cursor->terminal_size.ws_row); // debug here !!!!
  while (pos_y < cursor->terminal_size.ws_row)
  {
    ft_cursor_move_x(0, cursor->move_x);
    ft_term_apply_cmd(cursor->clear_current_line, 1);
    ft_term_apply_cmd(cursor->up, 1);
    pos_y++;
  }
  // ft_term_apply_cmd(cursor->restore_cursor_position, 1);
  return (EXIT_SUCCESS);
}

/**
 * clear the actual line and reprint from line - 1 to line - 1
 */
int  ft_cursor_scroll_up(t_cursor *cursor, t_arr *arr)
{
  void *s_line;
  int index_start_showed;
  int len_tmp;
  int index_end_showed;

  cursor->y_start--;
  ft_cursor_clear_all_screen(cursor);
  // ft_term_apply_cmd(cursor->up, cursor->terminal_size.ws_row);
  ft_cursor_move_x(0, cursor->move_x);
  s_line = arr->ptr;
  len_tmp = arr->length;
  // index_start_showed = ft_cursor_index_prev_line_start(cursor, arr);
  index_start_showed = ft_index_line_start_showed(cursor, arr);
  // ft_putstr("\nindex_start_showed: ");ft_putnbr(index_start_showed);ft_putstr("\n");
  index_end_showed = ft_cursor_index_prev_line_end(cursor, arr, index_start_showed);
  // ft_putstr("\nindex_end_showed: ");ft_putnbr(index_end_showed);ft_putstr("\n");

  arr->length = index_end_showed + 1 - index_start_showed;
  // ft_putstr("\narr->length: ");ft_putnbr(arr->length);ft_putstr("\n");

  if ((cursor->pos_y - 1) == 0)
  {
    ft_putstr(cursor->prompt);
  }
  arr->ptr = (unsigned char *)arr->ptr + arr->sizeof_elem * index_start_showed;
  ft_arr_print(arr);
  arr->length = len_tmp;
  arr->ptr = s_line;
  ft_term_apply_cmd(cursor->up, 1);
  // ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  return (EXIT_SUCCESS);
}


/**
 * if the cursor position is on the first col
 */

static int  ft_cursor_left_up_line(t_cursor *cursor, t_arr *arr, unsigned char *s_line)
{
  if (cursor->pos_y)
  {
    if (cursor->pos_y == cursor->y_start)
    {
      // ft_move_left_bw();
      ft_cursor_scroll_up(cursor, arr);
      // cursor->y_start--;
    }
    else
    {
      ft_term_apply_cmd(cursor->up, 1);
    }

    cursor->pos_y--;
    cursor->pos_x = cursor->terminal_size.ws_col - 1;
    ft_cursor_move_x(cursor->pos_x, cursor->move_x);
    if (s_line[4] == 1)
    {
      ft_cursor_left_tab(cursor, 1);
    }
    else if (*s_line == 10)
    {
      ft_cursor_left_chariot(cursor, arr);
    }
    else
    {
      cursor->index_line--;
    }
  }
  return (EXIT_SUCCESS);
}

/**
 * move the cursor to current position - 1 on the same line or line - 1 if
 * actual position is 0
 */

int  ft_cursor_left(t_cursor *cursor, t_arr *arr)
{
  unsigned char *s_line;

  // ft_term_apply_cmd(cursor->left, 3);
  // ft_move_left_bw();
  if ((cursor->index_line - 1) >= 0
  && cursor->left && cursor->up && cursor->move_x)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem *
    (cursor->index_line - 1);
    s_line = *(unsigned char **)s_line;
    if (cursor->pos_x)
    {
      ft_cursor_left_same_line(cursor, s_line);
    }
    else
    {
      ft_cursor_left_up_line(cursor, arr, s_line);
    }
  }
  return (EXIT_SUCCESS);
}
