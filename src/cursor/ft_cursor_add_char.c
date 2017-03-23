/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_add_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:11:51 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 15:36:10 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** print the line after the cursor and reposition the cursor
*/

static int	ft_cursor_print_line(t_cursor *cursor, t_arr *arr, int index)
{
	ft_arr_print(arr);
	cursor->index_line = arr->length;
	ft_cursor_restore_y_x(
		cursor, arr, ft_cursor_nb_line_displayed(cursor, arr, 0, 0));
	ft_cursor_restore_index(cursor, arr, index);
	return (EXIT_SUCCESS);
}

/*
** add the new elem to arr and print
*/

static int	ft_add_char_isprint(t_cursor *cursor, t_arr *arr, char c)
{
	int		index;

	if (cursor->index_line == (int)arr->length)
	{
		ft_arr_add_char(cursor, arr, c, 0);
		ft_cursor_print_char(cursor, c, arr);
	}
	else
	{
		index = ft_cusor_clear_down_line(cursor, arr);
		cursor->index_line = index;
		ft_arr_add_char(cursor, arr, c, 0);
		index++;
		ft_cursor_print_line(cursor, arr, index);
	}
	return (EXIT_SUCCESS);
}

/*
** add the new elem return chariot to arr and print
*/

static int	ft_add_char_chariot(t_cursor *cursor, t_arr *arr)
{
	int		index;

	if (cursor->index_line == (int)arr->length)
	{
		ft_arr_add_char(cursor, arr, '\n', 0);
		ft_cursor_print_chariot(cursor, arr);
	}
	else
	{
		index = ft_cusor_clear_down_line(cursor, arr);
		cursor->index_line = index;
		ft_arr_add_char(cursor, arr, '\n', 0);
		cursor->y_total++;
		index++;
		ft_cursor_print_line(cursor, arr, index);
	}
	return (EXIT_SUCCESS);
}

/*
** add four space to arr like a tabulation and print
*/

static int	ft_add_char_tab(t_cursor *cursor, t_arr *arr)
{
	int		index_tab;
	int		index;

	index_tab = -1;
	while (++index_tab < TABULATION_LEN)
		if (cursor->index_line == (int)arr->length)
		{
			ft_arr_add_char(cursor, arr, ' ', 1);
			ft_cursor_print_char(cursor, ' ', arr);
		}
	if (cursor->index_line != (int)arr->length)
	{
		index = ft_cusor_clear_down_line(cursor, arr);
		cursor->index_line = index;
		ft_arr_add_char(cursor, arr, ' ', 1);
		ft_arr_add_char(cursor, arr, ' ', 1);
		ft_arr_add_char(cursor, arr, ' ', 1);
		ft_arr_add_char(cursor, arr, ' ', 1);
		index += 4;
		ft_cursor_print_line(cursor, arr, index);
	}
	return (EXIT_SUCCESS);
}

/*
** add char to t_arr *arr (current line)
** print the char
** fail if is not a printable char
*/

int			ft_cursor_add_char(t_cursor *cursor, t_arr *arr, char *buff)
{
	char		*buff_tmp;

	if (!cursor || !buff)
		return (EXIT_FAILURE);
	ft_term_apply_cmd(cursor->mode_insertion, 1);
	buff_tmp = buff;
	while (*buff_tmp)
	{
		if (ft_isprint(*buff_tmp))
		{
			ft_add_char_isprint(cursor, arr, *buff_tmp);
		}
		else if (*buff_tmp == 9)
		{
			ft_add_char_tab(cursor, arr);
		}
		else if (*buff_tmp == 10)
		{
			ft_add_char_chariot(cursor, arr);
		}
		buff_tmp++;
	}
	return (EXIT_SUCCESS);
}
