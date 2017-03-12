/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_clear_down.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:09:21 by alex              #+#    #+#             */
/*   Updated: 2017/03/12 17:11:56 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/**
 * clear all the screen below the cursor position line , including the current line
 */
int  ft_cursor_clear_down(t_cursor *cursor)
{
  int pos_y_tmp;

  pos_y_tmp = 0;
  ft_term_apply_cmd(cursor->save_cursor_position, 1);
  ft_cursor_move_x(0, cursor->move_x);
  while (pos_y_tmp < cursor->terminal_size.ws_row)
  {
    ft_term_apply_cmd(cursor->clear_current_line, 1);
    ft_term_apply_cmd(cursor->down, 1);
    pos_y_tmp++;
  }
  ft_term_apply_cmd(cursor->restore_cursor_position, 1);
  return (EXIT_SUCCESS);
}
