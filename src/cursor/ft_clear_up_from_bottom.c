/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_up_from_bottom.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:36:09 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 10:36:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/*
 * clear the screen from the bottom line
 */
int  ft_clear_up_from_bottom(t_cursor *cursor)
{
  int i;

  i = 0;
  ft_cursor_move_x(0, cursor->move_x);
  while (i < cursor->terminal_size.ws_row)
  {
    ft_term_apply_cmd(cursor->clear_current_line, 1);
    ft_term_apply_cmd(cursor->up, 1);
    i++;
  }
  return (EXIT_SUCCESS);
}
