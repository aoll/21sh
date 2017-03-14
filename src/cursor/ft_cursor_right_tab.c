/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_right_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:33:27 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 10:33:49 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/*
 * if the next char is a tabulation, the cursor must move the TABULATION_LEN
 * if the the first space is on the same line than the cursor before mouve
 * same_line = 0 else same_line = 1
 */
int  ft_cursor_right_tab(t_cursor *cursor, int same_line)
{
  int index_tab;

  index_tab = 0;
  index_tab += same_line;
  while (index_tab < TABULATION_LEN)
  {
    ft_term_apply_cmd(cursor->right, 1);
    cursor->pos_x++;
    cursor->index_line++;
    index_tab++;
    if (cursor->pos_x + 1 == cursor->terminal_size.ws_col
      && index_tab < TABULATION_LEN)
    {
      cursor->pos_y++;
      ft_term_apply_cmd(cursor->down, 1);
      cursor->pos_x = 0;
      ft_cursor_move_x(cursor->pos_x, cursor->move_x);
      index_tab++;
      cursor->index_line++;
    }
  }
  return (EXIT_SUCCESS);
}
