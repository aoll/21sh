/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_select_left.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:03:38 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 17:30:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_cursor_select_left_copy_cursor(t_cursor *new, t_cursor *old)
{
	new->index_line = old->index_line;
	new->pos_x = old->pos_x;
	new->pos_y = old->pos_y;
	new->y_start = old->y_start;
	new->prev_chariot = old->prev_chariot;
	return (EXIT_SUCCESS);
}

static int	ft_cursor_select_left_restore_cursor(
	t_cursor *cursor, t_cursor *cursor_tmp, t_arr *arr, char *s_line)
{
	ft_term_apply_cmd(cursor->mode_insertion, 1);
	ft_term_apply_cmd(cursor->mode_basic_video, 1);
	ft_cursor_select_left_copy_cursor(cursor, cursor_tmp);
	if (!cursor->pos_x && *s_line != 10)
	{
		ft_cursor_move_x(cursor->pos_x, cursor->move_x);
		ft_term_apply_cmd(cursor->down, 1);
	}
	ft_cursor_left(cursor, arr);
	return (EXIT_SUCCESS);
}

static int	ft_cursor_select_left_set_mode(
	t_cursor *cursor, char *s_line, int *is_will_reverse)
{
	if (s_line[5] != 1)
	{
		*is_will_reverse = 1;
		ft_term_apply_cmd(cursor->mode_reverse_video, 1);
	}
	ft_term_apply_cmd(cursor->mode_insertion_end, 1);
	return (EXIT_SUCCESS);
}

/*
** select the char left to the cursor
*/


int	ft_cursor_select_left(t_cursor *cursor, t_arr *arr, t_arr *select_line)
{
	char			*s_line;
	int				err;
	int				is_will_reverse;
	t_cursor		cursor_tmp;

	ft_cursor_select_left_copy_cursor(&cursor_tmp, cursor);
	is_will_reverse = 0;
	if ((err = ft_cursor_left(cursor, arr)))
		return (EXIT_FAILURE);
	s_line = *(char **)((
		unsigned char *)arr->ptr + arr->sizeof_elem * (cursor->index_line));
	ft_cursor_select_left_set_mode(cursor, s_line, &is_will_reverse);
	if (s_line[4] == 1)
	{
		ft_cursor_select_overide_tab(cursor, arr, select_line, is_will_reverse);
	}
	else
	{
		ft_cursor_select_overide_char(cursor, arr, select_line, is_will_reverse);
	}
	ft_cursor_select_left_restore_cursor(cursor, &cursor_tmp, arr, s_line);
	return (EXIT_SUCCESS);
}
