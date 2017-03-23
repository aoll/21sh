/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_del_or_suppr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 18:39:15 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 15:53:38 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_cursor_arr_pop_elem_set_cursor(
	t_cursor *cursor, t_arr *arr, char *s_line)
{
	if (*s_line == '"')
		if (!cursor->quote)
		{
			cursor->dquote = !cursor->dquote;
			if (ft_check_is_char(arr, '\''))
			{
				cursor->dquote = false;
				cursor->quote = true;
			}
		}
	if (*s_line == '\'')
		if (!cursor->dquote)
		{
			cursor->quote = !cursor->quote;
			if (ft_check_is_char(arr, '"'))
			{
				cursor->quote = false;
				cursor->dquote = true;
			}
		}
	return (EXIT_SUCCESS);
}

static int	ft_cursor_arr_pop_elem_tabulation(
	t_arr *arr, int index_line_tmp, int is_prev_char)
{
	int		index_tab;
	void	*s;

	index_tab = -1;
	while (++index_tab < TABULATION_LEN)
	{
		if ((s = ft_arr_pop(arr, (index_line_tmp -= is_prev_char))))
			free(s);
	}
	return (EXIT_SUCCESS);
}

/*
** pop a elem to arr and four elem if the elem at the index in parameter is
** marked like a tab
** is_prev_char		is equal to 1 if is the elem before, 0 if is the pointed
** by the the index is targeted
** return the new index
*/

static int	ft_cursor_arr_pop_elem(t_arr *arr, t_cursor *cursor,
	int index_line_tmp, int is_prev_char)
{
	char		*s_line;
	void		*s;

	s_line = *(char **)((unsigned char *)arr->ptr + arr->sizeof_elem *
	(index_line_tmp - is_prev_char));
	ft_cursor_arr_pop_elem_set_cursor(cursor, arr, s_line);
	if (s_line[4] == 1)
	{
		ft_cursor_arr_pop_elem_tabulation(arr, index_line_tmp, is_prev_char);
	}
	else
	{
		if (*s_line == 10)
		{
			cursor->chariot--;
			if (is_prev_char)
				cursor->prev_chariot--;
		}
		if ((s = ft_arr_pop(arr, (index_line_tmp -= is_prev_char))))
			free(s);
	}
	return (index_line_tmp);
}

static int	ft_cursor_del_or_suppr_set_cursor(
	t_cursor *cursor, t_arr *arr, int *is_prev_char)
{
	if (*is_prev_char)
	{
		ft_cursor_left(cursor, arr);
	}
	*is_prev_char = 0;
	ft_term_apply_cmd(cursor->save_cursor_position, 1);
	return (EXIT_SUCCESS);
}

/*
** delete the prev char		if is_prev_char		is equal to 1
** delete the actual char		if is_prev_char		is equal to 0
*/

int			ft_cursor_del_or_suppr(
	t_cursor *cursor, t_arr *arr, int is_prev_char)
{
	t_cursor	cursor_tmp;
	int			err;

	ft_cursor_del_or_suppr_set_cursor(cursor, arr, &is_prev_char);
	cursor_tmp.index_line = cursor->index_line;
	cursor_tmp.pos_y = cursor->pos_y;
	cursor_tmp.pos_x = cursor->pos_x;
	cursor_tmp.chariot = cursor->chariot;
	if (!cursor || (cursor->index_line - is_prev_char) < 0 ||
	!cursor->clear_down || !cursor->left)
		return (EXIT_FAILURE);
	if ((err = ft_cursor_move_to_start(cursor, arr))
	|| (err = ft_term_apply_cmd(cursor->clear_down, 1)))
		return (EXIT_FAILURE);
	cursor_tmp.index_line = ft_cursor_arr_pop_elem(
		arr, cursor, cursor_tmp.index_line, is_prev_char);
	ft_restore_prompt_and_line(cursor, arr);
	cursor->index_line = cursor_tmp.index_line;
	cursor->pos_x = cursor_tmp.pos_x;
	cursor->pos_y = cursor_tmp.pos_y;
	ft_term_apply_cmd(cursor->restore_cursor_position, 1);
	return (EXIT_SUCCESS);
}
