#include "project.h"
// /**
//  * move the cursor to a actual position x - 1 (left)
//  */
//
int  ft_move_left_bw(void)
{
  char *cmd;
  char *cmd2;
  char *cmd3;


  if ((cmd2 = tgetstr("ho", NULL)) == NULL) //move to the left
    ft_putstr("NULLLLLLLLLLLL\n");
    // return (EXIT_FAILURE); //pas quiter le programme

  // tputs(cmd2, 0, &my_putchar);
  if ((cmd = tgetstr("sr", NULL)) == NULL) //move to the left
    ft_putstr("NULLLLLLLLLLLL\n");
    // return (EXIT_FAILURE); //pas quiter le programme

    // return (EXIT_FAILURE); //pas quiter le programme

  tputs(cmd, 0, &my_putchar);
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
 * if the cursor position is on the first col
 */

static int  ft_cursor_left_up_line(t_cursor *cursor, t_arr *arr, unsigned char *s_line)
{
  if (cursor->pos_y)
  {
    if (cursor->pos_y < cursor->terminal_size.ws_row
      && cursor->y_total > cursor->terminal_size.ws_row)
    {
      // ft_term_apply_cmd(cursor->scroll_, 1);
      ft_move_left_bw();
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
