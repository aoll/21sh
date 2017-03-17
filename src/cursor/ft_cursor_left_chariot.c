/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_left_chariot.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 08:55:39 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 16:21:44 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/*
** the cursor is on the last col after a return chariot
** il will be just after the char on the return chariot
*/

int	ft_cursor_left_chariot(t_cursor *cursor, t_arr *arr)
{
	int		nb_char;

	cursor->prev_chariot--;
	cursor->index_line--;
	if (cursor->prev_chariot)
	{
		nb_char = ft_nb_char_between_two_chariot(arr, cursor->index_line - 1);
		if (nb_char > cursor->terminal_size.ws_col)
		 nb_char = nb_char % cursor->terminal_size.ws_col;
		if (!cursor->pos_y)
		{
		 nb_char += cursor->prompt_len;
		}
	}
	else
	{
		nb_char = (cursor->prompt_len + cursor->index_line)
		% cursor->terminal_size.ws_col;
	}
	cursor->pos_x = nb_char;
	ft_cursor_move_x(cursor->pos_x, cursor->move_x);
	return (EXIT_SUCCESS);
}
