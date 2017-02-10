/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_ctrl_c_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:07:55 by alex              #+#    #+#             */
/*   Updated: 2017/02/10 09:47:44 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * init the cursor for a new line
 */
int  ft_cursor_set_position(t_cursor *cursor)
{
  cursor->index_line = 0;
  cursor->pos_x = cursor->prompt_len;
  cursor->pos_y = 0;
  cursor->y_total = 1;
  cursor->prev_chariot = 0;
  cursor->chariot = 0;
  cursor->y_start = 0;
  cursor->dquote = false;
  cursor->quote = false;
  return (EXIT_SUCCESS);
}
/**
 * if the ctrl-c (SIGINT) was send
 * if some char is present in the line go the end , print '\n'
 * pop et free the currennt arr's elem and reprint prompt
 * else if not char print ^C\n and reprint prompt
 */
int  ft_read_ctrl_c_env(t_cursor *cursor, t_arr *arr)
{
  g_is_ctrl_c_father = 0;
  ft_cursor_end(cursor, arr);
  ft_putstr("^C\n");
  return (EXIT_SUCCESS);
}
