/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_left_same_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 08:53:26 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 08:53:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/**
 * if the cursor postion is not on the first col
 */
int  ft_cursor_left_same_line(t_cursor *cursor, unsigned char *s_line)
{
  if (!s_line)
  {
   return (EXIT_FAILURE);
  }
  if (s_line[4] == 1)
  {
    ft_cursor_left_tab(cursor, 0);
  }
  else
  {
    ft_term_apply_cmd(cursor->left, 1);
    cursor->pos_x--;
    cursor->index_line--;
  }
  return (EXIT_SUCCESS);
}
