/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_right_line_more_up.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 11:25:18 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 11:25:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int  ft_cursor_right_line_more_up(
  t_cursor *cursor, void *ptr_tmp, t_arr *arr)
{
  unsigned char *s_line;

  s_line = (unsigned char *)ptr_tmp + arr->sizeof_elem * cursor->index_line;
  s_line = *(unsigned char **)s_line;
  if ( *s_line == 10)
  {
    ft_term_apply_cmd(cursor->up, 1);
  }
  ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  return (EXIT_SUCCESS);
}
