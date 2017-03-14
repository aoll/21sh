/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_valide_line_init_cursor_prompt.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 12:26:40 by alex              #+#    #+#             */
/*   Updated: 2017/03/12 12:27:07 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * after enter, set the cursor to the begin of the line with his history++
 */
int  ft_cursor_valide_line_init_cursor_prompt(t_cursor *cursor, int len_history)
{
  cursor->index_history = len_history;
  cursor->index_line = 0;
  cursor->pos_x = cursor->prompt_len;
  cursor->pos_y = 0;
  cursor->y_total = 1;
  cursor->prev_chariot = 0;
  cursor->chariot = 0;
  cursor->y_start = 0;
  cursor->dquote = false;
  cursor->quote = false;
  ft_putstr(cursor->prompt);
  return (EXIT_SUCCESS);
}
