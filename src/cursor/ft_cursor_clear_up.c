/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_clear_up.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:08:24 by alex              #+#    #+#             */
/*   Updated: 2017/03/12 17:08:35 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/*
 * clear all the screen up the cursor position line , including the current line
 */
int  ft_cursor_clear_up(t_cursor *cursor)
{
  int pos_y_tmp;

  pos_y_tmp = cursor->pos_y;
  ft_cursor_move_x(0, cursor->move_x);
  while (pos_y_tmp > 0)
  {
    ft_term_apply_cmd(cursor->clear_current_line, 1);
    ft_term_apply_cmd(cursor->up, 1);
    pos_y_tmp--;
  }
  ft_term_apply_cmd(cursor->clear_current_line, 1);
  return (EXIT_SUCCESS);
}
