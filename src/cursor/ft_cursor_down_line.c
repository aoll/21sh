/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_down_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 08:45:02 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 16:18:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** if it's possible move the cursor to a position line + 1
*/

int	ft_cursor_down_line(t_cursor *cursor, t_arr *arr)
{
	int		pos_y_old;
	int		pos_x_old;
	int		mvt_x;

	if (cursor->pos_y == cursor->y_total - 1)
		return (EXIT_SUCCESS);
	pos_y_old = cursor->pos_y;
	pos_x_old = cursor->pos_x;
	mvt_x = cursor->pos_x;
	while (cursor->index_line < (int)arr->length)
	{
		ft_cursor_right(cursor, arr);
		if (cursor->pos_y == pos_y_old + 1)
			break;
	}
	while (cursor->index_line < (int)arr->length && mvt_x)
	{
		ft_cursor_right(cursor, arr);
		if (cursor->pos_y >= pos_y_old + 2)
			return (ft_cursor_left(cursor, arr));
		mvt_x--;
	}
	return (EXIT_SUCCESS);
}
