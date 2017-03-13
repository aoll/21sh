/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_select_overide_tab.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:04:20 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 12:04:38 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/**
 * if is_will_reverse = 1
 * add to select_line four space and overide in reverse video the four space
 * present on the screen
 * or
 * if is_will_reverse = 0 pop and free to select_line four space and overide
 * the four space presenet on the screen in basic video mode
 */
int  ft_cursor_select_overide_tab(t_cursor *cursor, t_arr *arr,
  t_arr *select_line, int is_will_reverse)
{
  int index_tab;
  unsigned char *s_line;

  index_tab = 0;
  while (index_tab < TABULATION_LEN)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (cursor->index_line + index_tab);
    s_line = *(unsigned char **)s_line;
    s_line[5] = is_will_reverse;
    if (is_will_reverse)
    {
      ft_arr_push(select_line, ft_strdup((char *)s_line), 0);
    }
    else if (select_line->length)
    {
      free(ft_arr_pop(select_line, select_line->length - 1));
    }
    ft_putstr((const char *)s_line);
    index_tab++;
  }
  return (EXIT_SUCCESS);
}
