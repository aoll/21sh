/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_cut.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 18:06:42 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 15:43:06 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
*
*/

static int	ft_cursor_cut_init(
	t_cursor *cursor, t_arr *arr, int *index_line_tmp, int *nb_line_displayed)
{
	*index_line_tmp = cursor->index_line;
	*nb_line_displayed = ft_cursor_nb_line_displayed(cursor, arr, 0, 0);
	ft_cursor_end(cursor, arr);
	ft_cursor_clear_up(cursor);
	return (EXIT_SUCCESS);
}

/*
*
*/

static int	ft_cursor_cut_process(t_arr *arr)
{
	int		index;
	char	*s_line;

	index = 0;
	while (index < (int)arr->length)
	{
		s_line = *(char **)(
			(unsigned char *)arr->ptr + arr->sizeof_elem * index);
		if (s_line[5] == 1)
		{
			free(ft_arr_pop(arr, index));
		}
		else
		{
			index++;
		}
	}
	return (EXIT_SUCCESS);
}

/*
** dup the selection in a new arr copy_line, and reprint the line without
** the selection
*/

int	ft_cursor_cut(
	t_cursor *cursor, t_arr *arr, t_arr *select_line, t_arr **copy_line)
{
	int		index_line_tmp;
	int		nb_line_displayed;

	ft_cursor_cut_init(cursor, arr, &index_line_tmp, &nb_line_displayed);
	ft_cursor_copy_line(cursor, select_line, copy_line);
	while (select_line->length)
	{
		free(ft_arr_pop(select_line, 0));
	}
	ft_cursor_cut_process(arr);
	if (index_line_tmp > (int)arr->length)
	{
		index_line_tmp = arr->length;
	}
	cursor->index_line = arr->length;
	nb_line_displayed = ft_cursor_nb_line_displayed(cursor, arr, 0, 0);
	ft_putstr(cursor->prompt);
	ft_arr_print(arr);
	ft_cursor_restore_y_x(cursor, arr, nb_line_displayed);
	ft_cursor_restore_index(cursor, arr, index_line_tmp);
	return (EXIT_SUCCESS);
}
