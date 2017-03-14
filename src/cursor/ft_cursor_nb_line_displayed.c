/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_nb_line_displayed.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:25:37 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 09:33:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int  ft_cursor_nb_line_set_cursor(
  t_cursor *cursor, t_arr *arr, unsigned char *s_line, int index_start_showed)
{
  if (index_start_showed >= (int)arr->length && *s_line != 10)
  {
    ft_putchar('Z');
    ft_term_apply_cmd(cursor->left, 1);
    ft_term_apply_cmd(cursor->sup_char, 1);
  }
  return (EXIT_SUCCESS);
}

static int  ft_cursor_nb_line_init(
  t_cursor *cursor, int *nb_line, int *index_line, int index_start_showed)
{
  *nb_line = 1;
  *index_line = 0;
  if (!index_start_showed)
    *index_line = cursor->prompt_len;
  return (EXIT_SUCCESS);
}
/*
 * return the number of the line actualy displayed
 */
int  ft_cursor_nb_line_displayed(
  t_cursor *cursor, t_arr *arr, int index_start_showed, int is_total)
{
  int index_line;
  int nb_line;
  unsigned char *s_line;

  ft_cursor_nb_line_init(cursor, &nb_line, &index_line, index_start_showed);
  while (index_start_showed < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * index_start_showed;
    s_line = *(unsigned char **)s_line;
    if (nb_line == cursor->terminal_size.ws_row && !is_total)
      return (nb_line);
    index_start_showed++;
    if (index_line == cursor->terminal_size.ws_col - 1 || *s_line == 10)
    {
      index_line = -1;
      nb_line++;
      ft_cursor_nb_line_set_cursor(cursor, arr, s_line, index_start_showed);
    }
    index_line++;
  }
  return (nb_line);
}
