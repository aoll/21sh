/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_resize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 09:25:52 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 17:00:01 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** restore the cursor postion in function of the index give in parameter
*/

int	ft_cursor_restore_index(t_cursor *cursor, t_arr *arr, int index)
{
	ft_cursor_home(cursor, arr);
	while (cursor->index_line != index)
	{
		ft_cursor_right(cursor, arr);
	}
	return (EXIT_SUCCESS);
}

/*
** clean only the line
*/

int	ft_cursor_clear_only_the_line(t_cursor *cursor, t_arr *arr)
{
	ft_cursor_end(cursor, arr);
	ft_cursor_clear_up(cursor);
	return (EXIT_SUCCESS);
}

/*
** reprint the line with the new size
*/

int	ft_cursor_print_after_resize(
	t_cursor *cursor, t_arr *arr, int nb_line_displayed)
{
	int				index_line_tmp;

	index_line_tmp = cursor->index_line;
	ft_term_apply_cmd(cursor->clear_all_the_screen, 1);
	cursor->index_line = arr->length;
	ft_putstr(cursor->prompt);
	ft_arr_print(arr);
	ft_cursor_restore_y_x(cursor, arr, nb_line_displayed);
	ft_cursor_restore_index(cursor, arr, index_line_tmp);
	return (EXIT_SUCCESS);
}

/*
** reprint the line in function of the size screen
*/

int	ft_cursor_resize(
	t_cursor *cursor, t_arr *arr, struct winsize *terminal_size_old)
{
	int				index_start_showed;
	int				nb_line_displayed_old;
	int				nb_line_displayed_new;
	struct winsize	terminal_size_tmp;

	terminal_size_tmp = cursor->terminal_size;
	index_start_showed = ft_index_line_start_showed(cursor, arr);
	nb_line_displayed_old = ft_cursor_nb_line_displayed(cursor, arr, 0, 1);
	cursor->terminal_size.ws_col = terminal_size_old->ws_col;
	cursor->terminal_size.ws_row = terminal_size_old->ws_row;
	nb_line_displayed_new = ft_cursor_nb_line_displayed(cursor, arr, 0, 0);
	ft_cursor_print_after_resize(cursor, arr, nb_line_displayed_new);
	return (EXIT_SUCCESS);
}
