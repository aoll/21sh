#include "project.h"

/**
 * add the current_line to the history_line (history command)
 * exec the current_line
 * show a new prompt
 */
int  ft_cursor_valide_line(t_cursor *cursor, t_arr **history_line, t_arr **current_line, t_arr **arr)
{
  t_arr *tmp_arr;
  t_arr *tmp_current_line;
  t_arr *tmp_history_line;
  t_arr *line_tmp;
  t_arr *invalide_line;

  tmp_arr = *arr;
  tmp_current_line = *current_line;
  tmp_history_line = *history_line;
  ft_cursor_end(cursor, tmp_arr);
  if (tmp_current_line->length == 1 && tmp_arr->length)
  {
    ft_arr_push(tmp_current_line, ft_arr_dup(tmp_arr), -1);
    invalide_line = *(t_arr **)((unsigned char *)tmp_history_line->ptr + (tmp_history_line->length - 1) * tmp_history_line->sizeof_elem);
    if (invalide_line->length < 2)
    {
      ft_arr_free(ft_arr_pop(&invalide_line, 0));
      ft_arr_free(ft_arr_pop(&tmp_history_line, tmp_history_line->length - 1));
    }
  }
  else if (tmp_current_line->length == 1 && !tmp_arr->length)
  {
    invalide_line = *(t_arr **)((unsigned char *)tmp_history_line->ptr + (tmp_history_line->length - 1) * tmp_history_line->sizeof_elem);
    if (invalide_line->length < 2)
    {

      ft_arr_free(ft_arr_pop(&invalide_line, 0));
      ft_arr_free(ft_arr_pop(&tmp_history_line, tmp_history_line->length - 1));
    }
  }
  else if (tmp_current_line->length >= 2 && tmp_arr->length)
  {
    invalide_line = *(t_arr **)((unsigned char *)tmp_history_line->ptr + (tmp_history_line->length - 1) * tmp_history_line->sizeof_elem);
    if (invalide_line->length < 2)
    {
      ft_arr_free(ft_arr_pop(&invalide_line, 0));
      ft_arr_free(ft_arr_pop(&tmp_history_line, tmp_history_line->length - 1));
    }
    line_tmp = ft_arr_new(2, sizeof(t_arr *));
    ft_arr_push(line_tmp, ft_arr_dup(tmp_arr), 0);
    ft_arr_push(line_tmp, ft_arr_dup(tmp_arr), 1);
    ft_arr_push(tmp_history_line, line_tmp, -1);
    //TODO  free tmp_current_line!!!!!
    ft_arr_free(ft_arr_pop(&tmp_current_line, 1));

    tmp_arr = *(t_arr **)tmp_current_line->ptr;
    ft_arr_push(tmp_current_line, ft_arr_dup(tmp_arr), 1);
  }
  else if (tmp_current_line->length >= 2 && !tmp_arr->length)
  {
    invalide_line = *(t_arr **)((unsigned char *)tmp_history_line->ptr + (tmp_history_line->length - 1) * tmp_history_line->sizeof_elem);
    if (invalide_line->length < 2)
    {
      ft_arr_free(ft_arr_pop(&invalide_line, 0));
      ft_arr_free(ft_arr_pop(&tmp_history_line, tmp_history_line->length - 1));
    }
  }
  cursor->index_history = 0;
  while (cursor->index_history < (int)tmp_history_line->length)
  {
    line_tmp = *(t_arr **)((unsigned char *)tmp_history_line->ptr + cursor->index_history * tmp_history_line->sizeof_elem);

    ft_arr_free(ft_arr_pop(&line_tmp, 1));
    tmp_arr = *(t_arr **)line_tmp->ptr;
    tmp_arr = ft_arr_dup(tmp_arr);
    if (tmp_arr)
    {
      ft_arr_push(line_tmp, tmp_arr, 1);
    }
    cursor->index_history++;
  }

  tmp_arr = ft_arr_new(1, sizeof(char*));
  tmp_arr->f_print = &ft_arr_putchar;
  tmp_arr->f_dup_elem = &ft_arr_strdup;
  tmp_current_line = ft_arr_new(1, sizeof(t_arr*));
  ft_arr_push(tmp_current_line, tmp_arr, 0);
  ft_arr_push(tmp_history_line, tmp_current_line, -1);
  cursor->index_history = tmp_history_line->length - 1; // yes, because, when you press enter is a new line
  cursor->index_line = 0;
  cursor->pos_x = cursor->prompt_len;
  cursor->pos_y = 0;
  cursor->y_total = 1;
  cursor->prev_chariot = 0;
  cursor->chariot = 0;
  cursor->y_start = 0;
  // ft_putstr("\n");
  ft_putstr(cursor->prompt);
  *arr = tmp_arr;
  *current_line = tmp_current_line;
  *history_line = tmp_history_line;

  return (EXIT_SUCCESS);
}
