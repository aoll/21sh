/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_select_overide_char.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:05:16 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 12:05:34 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/*
 * if is_will_reverse = 1
 * add to select_line the char and overide in reverse video the char
 * present on the screen
 * or
 * if is_will_reverse = 0 pop and free to select_line a char and overide
 * the char present on the screen in basic video mode
 */
int  ft_cursor_select_overide_char(t_cursor *cursor, t_arr *arr,
  t_arr *select_line, int is_will_reverse)
{
  unsigned char *s_line;

  s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (cursor->index_line);
  s_line = *(unsigned char **)s_line;
  ft_putstr((const char *)s_line);
  s_line[5] = is_will_reverse;
  if (is_will_reverse)
  {
    ft_arr_push(select_line, ft_strdup((const char *)s_line), 0);
  }
  else
  {
    free(ft_arr_pop(select_line, select_line->length - 1));
  }
  return (EXIT_SUCCESS);
}
