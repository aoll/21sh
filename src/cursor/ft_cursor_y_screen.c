/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_y_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 11:27:18 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 11:28:18 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/**
 * return the y position of the cursor compare to the screen
 */
int  ft_cursor_y_screen(t_cursor *cursor, t_arr *arr)
{
  int index_start_showed;
  int nb_line;
  int index_line;
  unsigned char *s_line;

  index_start_showed = ft_index_line_start_showed(cursor, arr);
  nb_line = 0;
  index_line = 0;
  while (index_start_showed < (int)arr->length)
  {
    s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * index_start_showed;
    s_line = *(unsigned char **)s_line;
    if (index_start_showed == cursor->index_line)
      return (nb_line);
    if (index_line == cursor->terminal_size.ws_col - 1 || *s_line == 10)
    {
      index_line = -1;
      nb_line++;
    }
    index_line++;
    index_start_showed++;
  }
  return (nb_line);
}
