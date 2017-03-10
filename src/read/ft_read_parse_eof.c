/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_parse_eof.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:56:36 by alex              #+#    #+#             */
/*   Updated: 2017/03/10 15:56:56 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

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
        ft_arr_free(ft_arr_pop(current_line_free, index_current_free));
      }
      ft_arr_free(ft_arr_pop(history_line, index_history_free));
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
