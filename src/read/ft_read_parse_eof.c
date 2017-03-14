/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_parse_eof.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:56:36 by alex              #+#    #+#             */
/*   Updated: 2017/03/11 15:45:38 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"


/*
 * free some arr and the cursor
 */
static int  ft_read_parse_eof_free_arr(t_cursor *cursor, t_list_arr *list_arr)
{
  ft_free_cursor(cursor);
  if (list_arr->select_line)
  {
    ft_arr_free(list_arr->select_line);
  }
  if (list_arr->copy_line)
  {
    ft_arr_free(list_arr->copy_line);
  }
  if (list_arr->env)
  {
    ft_arr_free(list_arr->env);
  }
  return (EXIT_SUCCESS);
}

/*
 * free arr history_line and inside elem and buff
 */
int  ft_read_parse_eof_free(t_cursor *cursor, t_list_arr *list_arr)
{
  int index_history_free;
  int index_current_free;
  t_arr *current_line_free;

  ft_read_parse_eof_free_arr(cursor, list_arr);
  index_history_free = 0;
  while (index_history_free < (int)list_arr->history_line->length)
  {
    current_line_free = *((t_arr **)(
      (unsigned char *)list_arr->history_line->ptr
      + index_history_free * list_arr->history_line->sizeof_elem));
    index_current_free = 0;
    while (index_current_free < (int)current_line_free->length)
    {
      ft_arr_free(ft_arr_pop(current_line_free, index_current_free));
    }
    ft_arr_free(ft_arr_pop(list_arr->history_line, index_history_free));
  }
  ft_arr_free(list_arr->history_line);
  free(list_arr->buff);
  list_arr->buff = NULL;
  return (EXIT_SUCCESS);
}

/*
 * if ctrl-d eof return 0
 * else return 1
 */
int  ft_read_parse_eof(t_cursor *cursor, t_list_arr *list_arr,
  struct termios *term, bool option)
{
  char *buff_ptr;

  buff_ptr = list_arr->buff;
  if ((buff_ptr[0] == 4 && !buff_ptr[1] && !buff_ptr[2] && !buff_ptr[3]
    && !buff_ptr[4] && !buff_ptr[5] && !buff_ptr[6] && !buff_ptr[7]) || option)
  {
    // si une ligne de commande est en cours exec ligne; ft_putstr("$> ");
    ft_read_parse_eof_free(cursor, list_arr);
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
