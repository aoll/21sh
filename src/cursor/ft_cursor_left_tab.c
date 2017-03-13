/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_left_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 08:52:13 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 08:52:34 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/**
 * if the prev char is a tabulation, the cursor must move the TABULATION_LEN
 * if the the first space is on the same line than the cursor before mouve
 * same_line = 0 else same_line = 1
 */
int  ft_cursor_left_tab(t_cursor *cursor, int same_line)
{
  int index_tab;

  index_tab = 0;
  cursor->index_line -= same_line;
  while (index_tab < TABULATION_LEN - same_line)
  {
    cursor->pos_x--;
    ft_term_apply_cmd(cursor->left, 1);
    cursor->index_line--;
    index_tab++;
    if (!cursor->pos_x && cursor->pos_y && index_tab < TABULATION_LEN)
    {
      ft_term_apply_cmd(cursor->up, 1);
      cursor->pos_y--;
      cursor->pos_x = cursor->terminal_size.ws_col - 1;
      ft_cursor_move_x(cursor->pos_x, cursor->move_x);
      cursor->index_line--;
      index_tab++;
    }
  }
  return (EXIT_SUCCESS);
}
