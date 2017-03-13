/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_right_chariot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:34:27 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 10:34:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/**
 * cursor is actually on a '\n' move down one time and place the cursor and the
 * first col
 */
int  ft_cursor_right_chariot(t_cursor *cursor)
{
  cursor->prev_chariot++;
  cursor->pos_y++;
  cursor->pos_x = 0;
  cursor->index_line++;
  ft_term_apply_cmd(cursor->down, 1);
  ft_cursor_move_x(cursor->pos_x, cursor->move_x);
  return (EXIT_SUCCESS);
}
