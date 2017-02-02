#include "project.h"


/**
 * clear all the screen and restore the position of the cursor
 */
int  ft_cursor_clear_resize(t_cursor *cursor, int is_up)
{
  int pos_y;

  pos_y = 0;
  // ft_term_apply_cmd(cursor->save_cursor_position, 1);
  ft_term_apply_cmd(cursor->up, cursor->terminal_size.ws_row - 1); // debug here !!!!
  if (is_up)
  {
    ft_term_apply_cmd(cursor->down, cursor->terminal_size.ws_row - 1); // debug here !!!!
  }
  // ft_term_apply_cmd()
  ft_cursor_move_x(0, cursor->move_x);
  while (pos_y < cursor->terminal_size.ws_row)
  {
    ft_term_apply_cmd(cursor->clear_current_line, 1);
    ft_term_apply_cmd(cursor->up, 1);
    pos_y++;
  }
  // ft_term_apply_cmd(cursor->restore_cursor_position, 1);
  return (EXIT_SUCCESS);
}

/**
 * return the number of the line actualy displayed
 */
int  ft_cursor_nb_line_displayed(t_cursor *cursor, t_arr *arr, int index_start_showed, int is_total)
{
  int index_line;
  int nb_line;
  unsigned char *s_line;

  nb_line = 1;
  index_line = 0;
  if (!index_start_showed)
  {
    index_line = cursor->prompt_len;
  }
  while (index_start_showed < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * index_start_showed;
    s_line = *(unsigned char **)s_line;
    if (nb_line == cursor->terminal_size.ws_row && !is_total)
    {
      return (nb_line);
    }
    if (index_line == cursor->terminal_size.ws_col - 1 || *s_line == 10)
    {
      index_line = 0;
      nb_line++;
      index_start_showed++;
      if (index_start_showed >= (int)arr->length && *s_line != 10)
      {
        ft_putchar('Z');
        ft_term_apply_cmd(cursor->left, 1);
        ft_term_apply_cmd(cursor->sup_char, 1);
      }
    }
    else
    {
      index_line++;
      index_start_showed++;
    }
  }
  return (nb_line);
}

/**
 * restore the cursor postion in function of the index give in parameter
 */
int  ft_cursor_restore_index(t_cursor *cursor, t_arr *arr, int index)
{
  ft_cursor_home(cursor, arr);
  while (cursor->index_line != index)
  {
    ft_cursor_right(cursor, arr);
  }
  return (EXIT_SUCCESS);
}

/**
 * clean only the line
 */
int  ft_cursor_clear_only_the_line(t_cursor *cursor, t_arr *arr)
{
  ft_cursor_end(cursor, arr);
  ft_cursor_clear_up(cursor);
  return (EXIT_SUCCESS);
}

/**
 * restore the pos_y and pos_y of the cursor
 */
int  ft_cursor_restore_y_x(t_cursor *cursor, t_arr *arr, int nb_line_displayed)
{
  int index;
  unsigned char *s_line;

  index = 0;
  cursor->pos_y = 0;
  cursor->pos_x = cursor->prompt_len;
  while (index < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + index * arr->sizeof_elem;
    s_line = *(unsigned char **)s_line;
    if (index == cursor->index_line)
    {
      cursor->y_start = cursor->pos_y - (nb_line_displayed - 1);
      return (EXIT_SUCCESS);
    }
    if (cursor->pos_x == cursor->terminal_size.ws_col - 1 || *s_line == 10)
    {
      cursor->pos_y++;
      cursor->pos_x = 0;
      index++;
    }
    else
    {
      cursor->pos_x++;
      index++;
    }
  }
  cursor->y_start = cursor->pos_y - (nb_line_displayed - 1);
  return (EXIT_SUCCESS);
}

/**
 * reprint the line with the new size
 */
int  ft_cursor_print_after_resize(t_cursor *cursor, t_arr *arr, int nb_line_displayed)
{
  int index_line_tmp;

  index_line_tmp = cursor->index_line;
  ft_term_apply_cmd(cursor->clear_all_the_screen, 1);
  cursor->index_line = arr->length;
  ft_putstr(cursor->prompt);
  ft_arr_print(arr);
  ft_cursor_restore_y_x(cursor, arr, nb_line_displayed);
  ft_cursor_restore_index(cursor, arr, index_line_tmp);
  return (EXIT_SUCCESS);
}

/**
 * reprint the line in function of the size screen
 */
int  ft_cursor_resize(t_cursor *cursor, t_arr *arr, struct winsize *terminal_size_old)
{

  int index_start_showed;
  int nb_line_displayed_old;
  int nb_line_displayed_new;
  struct winsize terminal_size_tmp;


  terminal_size_tmp = cursor->terminal_size;
  index_start_showed = ft_index_line_start_showed(cursor, arr);
  nb_line_displayed_old = ft_cursor_nb_line_displayed(cursor, arr, 0, 1);
  cursor->terminal_size.ws_col = terminal_size_old->ws_col;
  cursor->terminal_size.ws_row = terminal_size_old->ws_row;
  nb_line_displayed_new = ft_cursor_nb_line_displayed(cursor, arr, 0, 0);
  // if (nb_line_displayed_new + 1 > cursor->terminal_size.ws_row || nb_line_displayed_old + 1 > cursor->terminal_size.ws_row )
  // {
  ft_cursor_print_after_resize(cursor, arr, nb_line_displayed_new);
  return(0);
  // }
  // // nb_line_displayed = ft_cursor_nb_line_displayed(cursor, arr, index_start_showed);
  // // ft_putstr("\nnb_line_displayed can be");ft_putnbr(nb_line_displayed);ft_putstr("\n");


  // if (cursor->index_line == (int)arr->length && !((cursor->index_line + cursor->prompt_len) % terminal_size_old->ws_col))
  if (cursor->pos_x)
  {
    ft_putchar('Z');
    ft_term_apply_cmd(cursor->left, 1);
    ft_sup_char(1);

    // ft_cursor_restore_y_x(cursor, arr, nb_line_displayed_new);
  }
  // else
  // {
  //   ft_cursor_restore_y_x(cursor, arr, nb_line_displayed_new);
  // }
  return (EXIT_SUCCESS);
}
