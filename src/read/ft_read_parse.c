#include "project.h"

/**
 * function if a key with shift is pressed
 * if true return 0 else 1
 */
int  ft_read_parse_shift(const char *buff, t_cursor *cursor, t_arr *arr, t_arr **select_line)
{
  if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
    && buff[4] == 50 && buff[5] == 68 && !buff[6] && !buff[7]) // shift + left //done
  {
    cursor->is_select = true;
    if (cursor->index_line > 0 && arr->length && cursor->is_env)
    {
      ft_cursor_select_left(cursor, arr, *select_line);
    }
    return (EXIT_SUCCESS);
  }
  else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
    && buff[4] == 50 && buff[5] == 67 && !buff[6] && !buff[7])
  {
    cursor->is_select = true;
    if (cursor->index_line < (int)arr->length && cursor->is_env)
    {
      ft_cursor_select_right(cursor, arr, *select_line);
    }
    return (EXIT_SUCCESS);
  }
  return (EXIT_FAILURE);
}

/**
 * funcion if ctrl-up or ctrl-down is pressed
 * true return 0 else return 1
 */
int  ft_read_parse_ctrl(const char *buff, t_cursor *cursor, t_arr *arr)
{
  if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
    && buff[4] == 53 && buff[5] == 65 && !buff[6] && !buff[7])
  {
    if (cursor->is_env)
    {
      ft_cursor_up_line(cursor, arr);
    }
    return (EXIT_SUCCESS);
  }
  else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
    && buff[4] == 53 && buff[5] == 66 && !buff[6] && !buff[7])
  {
    if (cursor->is_env)
    {
      ft_cursor_down_line(cursor, arr);
    }
    return (EXIT_SUCCESS);
  }
  return (EXIT_FAILURE);
}

/**
 * up or down or key left or right return 0
 * else return 1
 */
int  ft_read_parse_arrow(
  const char *buff, t_cursor *cursor,
  t_arr **arr, t_arr *history_line, t_arr **current_line)
{
  if (buff[0] == 27 && buff[1] == 91 && (buff[2] == 65 || buff[2] == 66
    || buff[2] == 67 || buff[2] == 68) && !buff[3] && !buff[4] && !buff[5]
    && !buff[6] && !buff[7])
  {
    if (buff[2] == 65 && cursor->index_history - 1 >= 0 && cursor->is_env)
      ft_cursor_up_history_line(cursor, history_line, current_line, arr);
    else if (buff[2] == 66 && cursor->index_history +  1
      < (int)history_line->length && cursor->is_env)
      ft_cursor_down_history_line(cursor, history_line, current_line, arr);
    else if (buff[1] == 91 && buff[2] == 68 && cursor->is_env)
      ft_cursor_left(cursor, *arr);
    else if (buff[1] == 91 && buff[2] == 67 && cursor->is_env)
      ft_cursor_right(cursor, *arr);
    return (EXIT_SUCCESS);
  }
  return (EXIT_FAILURE);
}

/**
 * key home or end
 */
int  ft_read_parse_home_end(const char *buff, t_cursor *cursor, t_arr *arr)
{
  if (buff[0] == 27 && buff[1] == 91 && buff[2] == 72
    && !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7])
  {
    if (cursor->is_env)
    {
      ft_cursor_home(cursor, arr);
    }
  }
  else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 70
    && !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7])
  {
    if (cursor->is_env)
    {
      ft_cursor_end(cursor, arr);
    }
  }
  else
  {
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

/**
 * return 0 if is ctrl-left arrow or ctrl-rigth arrow
 */
int  ft_read_parse_ctrl_arrow(const char *buff, t_cursor *cursor, t_arr *arr)
{
  if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
    && buff[4] == 53 && buff[5] == 68 && !buff[6] && !buff[7])
  {
    if (cursor->index_line > 0 && cursor->is_env)
    {
      ft_cursor_word_left(cursor, arr);
    }
    return (EXIT_SUCCESS);
  }
  else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
    && buff[4] == 53 && buff[5] == 67 && !buff[6] && !buff[7])
  {
    if (cursor->index_line < (int)arr->length && cursor->is_env)
    {
      ft_cursor_word_right(cursor, arr);
    }
    return (EXIT_SUCCESS);
  }
  return (EXIT_FAILURE);
}

/**
 * return 0 if ctrl-x or ctrl-w or ctrl-v
 * else 1
 */
int  ft_read_parse_copy_cut_paste(
  const char *buff, t_cursor *cursor,
  t_arr *arr, t_arr *select_line, t_arr **copy_line)
{
  if (buff[0] == 24 && !buff[1] && !buff[2] && !buff[3] && !buff[4]
    && !buff[5] && !buff[6] && !buff[7])
  {
    cursor->is_select = false;
    if (!cursor->is_env)
      return (EXIT_SUCCESS);
    if (select_line->length)
      return (ft_cursor_cut(cursor, arr, select_line, copy_line));
  }
  else if (buff[0] == 23 && !buff[1] && !buff[2] && !buff[3] && !buff[4]
    && !buff[5] && !buff[6] && !buff[7])
  {
    cursor->is_select = true;
    if (!cursor->is_env)
      return (EXIT_SUCCESS);
    if (select_line->length)
      return (ft_cursor_copy_line(cursor, select_line, copy_line));
  }
  else if (buff[0] == 22 && !buff[1] && !buff[2] && !buff[3] && !buff[4]
    && !buff[5] && !buff[6] && !buff[7])
  {
    if (!cursor->is_env)
      return (EXIT_SUCCESS);
    if ((*copy_line)->length)
      return (ft_cursor_paste(cursor, arr, *copy_line));
  }
      // continue; ??
  return (EXIT_FAILURE);
}

/**
 * is del or suppr return 0
 * else return 1
 */
int  ft_read_parse_del_or_suppr(const char *buff, t_cursor *cursor, t_arr *arr)
{
  if (buff[0] == 127 && !buff[1] && !buff[2] && !buff[3] && !buff[4]
    && !buff[5] && !buff[6]  && !buff[7])
  {
    if (cursor->index_line > 0)
    {
      ft_cursor_del_or_suppr(cursor, arr, 1);
    }
    return (EXIT_SUCCESS);
  }
  else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 51
    && buff[3] == 126 && !buff[4] && !buff[5] && !buff[6]  && !buff[7])
  {
    if (arr->length && cursor->index_line < (int)arr->length)
    {
      ft_cursor_del_or_suppr(cursor, arr, 0);
    }
    return (EXIT_SUCCESS);
  }
  return (EXIT_FAILURE);
}

/**
 * if ctrl-d eof return 0
 * else return 1
 */
int  ft_read_parse_eof(char **buff, t_cursor *cursor,
  t_arr *arr, t_arr *history_line, t_arr *current_line,
  t_arr *copy_line, t_arr *select_line, struct termios *term, t_arr *env, bool option)
{
  char *buff_ptr;
  int index_history_free;
  int index_current_free;
  t_arr *current_line_free;

  buff_ptr = *buff;
  if ((buff_ptr[0] == 4 && !buff_ptr[1] && !buff_ptr[2] && !buff_ptr[3]
    && !buff_ptr[4] && !buff_ptr[5] && !buff_ptr[6] && !buff_ptr[7]) || option)
  {
    // si une ligne de commande est en cours exec ligne; ft_putstr("$> ");
    ft_free_cursor(cursor);
    if (select_line)
    {
      ft_arr_free(select_line);
    }
    if (copy_line)
    {
      ft_arr_free(copy_line);
    }
    if (env)
    {
      ft_arr_free(env);
    }
    index_history_free = 0;
    while (index_history_free < (int)history_line->length)
    {
      current_line_free = *((t_arr **)((unsigned char *)history_line->ptr + index_history_free * history_line->sizeof_elem));
      index_current_free = 0;
      while (index_current_free < (int)current_line_free->length)
      {
        ft_arr_free(ft_arr_pop(&current_line_free, index_current_free));
      }
      ft_arr_free(ft_arr_pop(&history_line, index_history_free));
      // index_history_free++;
    }
    ft_arr_free(history_line);
    free(*buff);
    *buff = NULL;
    ft_putchar('\n');
    if (cursor->is_env)
    {
      ft_term_apply_cmd(cursor->mode_insertion_end, 1);
      if (ft_get_term_restore(term))
      return (EXIT_SUCCESS);
    }
    return (EXIT_SUCCESS);
  }
  return (EXIT_FAILURE);
}

/**
 * orient in funtion of the pressed key different funtion
 */
int  ft_read_parse(
  const char *buff, t_cursor *cursor, t_arr **arr_ptr, t_arr *history_line,
  t_arr **current_line, t_arr **select_line, t_arr **copy_line)
{
  int err;
  t_arr *arr;

  arr = *arr_ptr;
  cursor->is_select = false;
  if (!(err = ft_read_parse_shift(buff, cursor, arr, select_line)))
    return (EXIT_SUCCESS);
  if (!(err = ft_read_parse_ctrl(buff, cursor, arr)))
    return (EXIT_SUCCESS);
  if (!(err = ft_read_parse_arrow(
    buff, cursor, arr_ptr, history_line, current_line)))
    return (EXIT_SUCCESS);
  if (!(err = ft_read_parse_home_end(buff, cursor, arr)))
    return (EXIT_SUCCESS);
  if (!(err = ft_read_parse_ctrl_arrow(buff, cursor, arr)))
    return (EXIT_SUCCESS);
  if (!(err = ft_read_parse_copy_cut_paste(
    buff, cursor, arr, *select_line, copy_line)))
    return (EXIT_SUCCESS);
  if (!(err = ft_read_parse_del_or_suppr(buff, cursor, arr)))
    return (EXIT_SUCCESS);

  return (EXIT_FAILURE);
}
