/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_deselect_all.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 15:53:58 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 15:54:50 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** cancel all reverse char marked after the index
*/

static int	ft_arr_cancel_reverse_video(
	t_arr *arr, int index, t_arr *select_line)
{
	unsigned char *s_line;

	while (index < (int)arr->length)
	{
		s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (index);
		s_line = *(unsigned char **)s_line;
		if (s_line[5] == 1)
		{
			s_line[5] = 0;
			free(ft_arr_pop(select_line, select_line->length - 1));
		}
		index++;
	}
	return (EXIT_SUCCESS);
}

/*
** set a tmp cursor
*/

static int	ft_cursor_deselect_all_set_tmp_cursor(
	t_cursor *end, t_cursor *cursor)
{
	end->index_line = cursor->index_line;
	end->pos_y = cursor->pos_y;
	end->pos_x = cursor->pos_x;
	end->y_start = cursor->y_start;
	end->prev_chariot = cursor->prev_chariot;
	end->chariot = cursor->chariot;
	return (EXIT_SUCCESS);
}

/*
** deselect all char and clean the t_arr select_line
** overide the line with a new line in basic video mode
*/

int			ft_cursor_deselect_all(
	t_cursor *cursor, t_arr *arr, t_arr *select_line)
{
	t_cursor		end;
	int				nb_line_displayed;

	if (!select_line->length || !cursor->save_cursor_position)
		return (EXIT_SUCCESS);
	ft_cursor_end(cursor, arr);
	ft_term_apply_cmd(cursor->save_cursor_position, 1);
	ft_cursor_deselect_all_set_tmp_cursor(&end, cursor);
	ft_cursor_home(cursor, arr);
	ft_arr_cancel_reverse_video(arr, 0, select_line);
	ft_term_apply_cmd(cursor->mode_insertion_end, 1);
	ft_arr_print(arr);
	cursor->index_line = arr->length;
	cursor->pos_y = end.pos_y;
	cursor->pos_x = end.pos_x;
	cursor->y_start = end.y_start;
	cursor->prev_chariot = end.prev_chariot;
	cursor->chariot = end.chariot;
	ft_term_apply_cmd(cursor->restore_cursor_position, 1);
	ft_cursor_restore_index(cursor, arr, end.index_line);
	ft_term_apply_cmd(cursor->mode_insertion, 1);
	return (EXIT_SUCCESS);
}
