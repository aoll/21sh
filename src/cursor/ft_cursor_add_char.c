#include "project.h"

/**
 * add a char to arr a marke if is a element to a tabulation
 */
int  ft_arr_add_char(t_cursor *cursor, t_arr *arr, char c, int is_tab)
{
  char *char_line;

  if (c == '"')
  {
    cursor->dquote = !cursor->dquote;
  }
  char_line = ft_strnew(8);
  ft_bzero(char_line, 8);
  *char_line = c;
  char_line[4] = is_tab;
  ft_arr_push(&arr, char_line, cursor->index_line);
  cursor->index_line++;
  return (EXIT_SUCCESS);
}

/**
 * print a char
 */
int  ft_cursor_print_char(t_cursor *cursor, char c)
{

  ft_putchar(c);
  cursor->pos_x++;
  if (cursor->pos_x >= cursor->terminal_size.ws_col)
  {
    ft_putchar('Z');
    ft_term_apply_cmd(cursor->left, 1);
    ft_term_apply_cmd(cursor->sup_char, 1);
    cursor->pos_x = 0;
    cursor->pos_y++;
    cursor->y_total++;
  }
  return (EXIT_SUCCESS);
}

/**
 * print a return chariot
 */
int  ft_cursor_print_chariot(t_cursor *cursor)
{

  ft_putchar('\n');
  cursor->pos_x = 0;
  cursor->pos_y++;
  cursor->y_total++;
  ft_cursor_move_x(cursor->pos_x, cursor->move_x);

  return (EXIT_SUCCESS);
}

/**
 * print from the cursor of the line and overide the old line
 */
int  ft_cursor_print_overide_line(t_cursor *cursor, t_arr *arr)
{
  t_arr tmp;
  int y_new;

  ft_term_apply_cmd(cursor->mode_insertion_end, 1);
  tmp.length = arr->length - (cursor->index_line);
  tmp.ptr = (unsigned char *)arr->ptr + cursor->index_line * arr->sizeof_elem;
  tmp.f_print = arr->f_print;
  tmp.sizeof_elem = arr->sizeof_elem;
  ft_arr_print(&tmp);
  if (!((cursor->prompt_len + arr->length) % cursor->terminal_size.ws_col))
  {
    ft_putchar('Z');
    ft_term_apply_cmd(cursor->left, 1);
    ft_term_apply_cmd(cursor->sup_char, 1);
  }
  y_new = (cursor->prompt_len + arr->length) / cursor->terminal_size.ws_col;
  ft_term_apply_cmd(cursor->up, y_new - cursor->pos_y);
  ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  return (EXIT_SUCCESS);
}

/**
 * add the new elem to arr and print
 */
int  ft_add_char_isprint(t_cursor *cursor, t_arr *arr, char c)
{
  ft_arr_add_char(cursor, arr, c, 0);
  if (cursor->index_line == (int)arr->length)
  {
    ft_cursor_print_char(cursor, c);
  }
  else
  {
    ft_cursor_print_char(cursor, c);
    ft_cursor_print_overide_line(cursor, arr);
  }
  return (EXIT_SUCCESS);
}
/**
 * add the new elem  return chariot to arr and print
 */
int  ft_add_char_chariot(t_cursor *cursor, t_arr *arr)
{
  cursor->prev_chariot++;
  cursor->chariot++;
  ft_arr_add_char(cursor, arr, '\n', 0);
  if (cursor->index_line == (int)arr->length)
  {
    ft_cursor_print_chariot(cursor);
  }
  else
  {
    ft_cursor_print_chariot(cursor);
    ft_cursor_print_overide_line(cursor, arr);
  }
  return (EXIT_SUCCESS);
}

/**
 * add four space to arr like a tabulation and print
 */
int  ft_add_char_tab(t_cursor *cursor, t_arr *arr)
{
  int index_tab;

  index_tab = -1;
  while (++index_tab < TABULATION_LEN)
  {
    ft_arr_add_char(cursor, arr, ' ', 1);
    if (cursor->index_line == (int)arr->length)
    {
      ft_cursor_print_char(cursor, ' ');
    }
    else
    {
      ft_cursor_print_char(cursor, ' ');
    }
  }
  if (cursor->index_line != (int)arr->length)
  {
    ft_cursor_print_overide_line(cursor, arr);
  }
  return (EXIT_SUCCESS);
}

/**
 * add char to t_arr *arr (current line)
 * print the char
 * fail if is not a printable char
 */
int  ft_cursor_add_char(t_cursor *cursor, t_arr *arr, char *buff)
{
  char *buff_tmp;

  if (!cursor || !buff)
  {
    return (EXIT_FAILURE);
  }
  ft_term_apply_cmd(cursor->mode_insertion, 1);
  buff_tmp = buff;
  while (*buff_tmp)
  {
    if (ft_isprint(*buff_tmp))
    {
      ft_add_char_isprint(cursor, arr, *buff_tmp);
    }
    else if (*buff_tmp == 9)
    {
      ft_add_char_tab(cursor, arr);
    }
    else if (*buff_tmp == 10)
    {
      ft_add_char_chariot(cursor, arr);
    }
    buff_tmp++;
  }
  return (EXIT_SUCCESS);
}


/**
 * add char to t_arr *arr (current line)
 * print the char
 * fail if is not a printable char
 */
int  ft_cursor_add_char_save(t_cursor *cursor, t_arr *arr, char *buff)
{
  char *buff_tmp;
  char *char_line;
  unsigned char *char_line_tmp;
  int index_tab;
  int nb_char = 0;

  buff_tmp = buff;
  while (*buff_tmp)
  {
    char_line = ft_strnew(8);
    ft_bzero(char_line, 8);
    if (cursor->char_tmp)
    {
      *char_line = cursor->char_tmp;
      *(char_line + 1) = *buff_tmp;
      cursor->char_tmp = 0;
    }
    else if (*buff_tmp < 0)
    {
      if (*(buff_tmp + 1) < 0)
      {
        ft_memcpy(char_line, buff_tmp, 2);
        buff_tmp++;
      }
      else
      {
        cursor->char_tmp = *buff_tmp;
        break;
      }
    }
    else
    {
      ft_memcpy(char_line, buff_tmp, 1);
    }

    // if (nb_char < cursor->terminal_size.ws_col)
    // {
    // ft_mode_insertion();
    if (*char_line == 9)
    {
      index_tab = 0;
      while (index_tab < TABULATION_LEN)
      {
        if (cursor->pos_x == cursor->terminal_size.ws_col)
        {
          ft_putchar('Z');
          ft_move_left();
          ft_sup_char(1);
          cursor->pos_y++;
          // ft_move_down(); test
          cursor->pos_x = 0;
          // ft_move_x(cursor->pos_x); test
        }
        if (index_tab)
        {
          char_line = ft_strnew(8);
          ft_bzero(char_line, 8);
        }
        *char_line = ' ';
        char_line[4] = 1;
        ft_arr_push(&arr, char_line, cursor->index_line);
        ft_mode_insertion();
        ft_putchar(' ');
        cursor->pos_x++;
        cursor->index_line++;
        nb_char++;
        index_tab++;
      }
    }
    else
    {
      ft_arr_push(&arr, char_line, cursor->index_line);
      if (nb_char + 1 > cursor->terminal_size.ws_col && nb_char > cursor->terminal_size.ws_col * (cursor->pos_y + 1))
      {
        ft_move_x(cursor->terminal_size.ws_col - 1);
        ft_sup_char(1);
        ft_move_down();
        ft_move_x(0);
        // rajout de la verification "qu'il ny est pas une tabulation sur le chemin"
        char_line_tmp  = (unsigned char *)arr->ptr + (cursor->index_line + cursor->terminal_size.ws_col - cursor->pos_x)  * arr->sizeof_elem;
        char_line_tmp = *(unsigned char **)char_line_tmp;
        ft_mode_insertion();
        ft_putchar(*char_line_tmp);
        ft_move_up();
        ft_move_x(cursor->pos_x);
        ft_mode_insertion();
        ft_putstr(char_line);

      }
      else
      {
        ft_mode_insertion();
        ft_putstr(char_line);
        nb_char++;
        cursor->pos_x++;
        cursor->index_line++;
      }
    }
    if (cursor->pos_x == cursor->terminal_size.ws_col)
    {
      cursor->pos_y++;
      ft_putchar('Z');
      ft_move_left();
      ft_sup_char(1);
      // ft_move_down(); test
      cursor->pos_x = 0;
      // ft_move_x(cursor->pos_x); test
    }
    // }
    buff_tmp++;
  }

  return (EXIT_SUCCESS);
}
