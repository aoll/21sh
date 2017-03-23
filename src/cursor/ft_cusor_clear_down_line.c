/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cusor_clear_down_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:56:22 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 17:37:59 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_cusor_clear_down_line_init(
	t_cursor *cursor, t_arr *arr, int *index, int *pos_y)
{
	*index = cursor->index_line;
	ft_cursor_home(cursor, arr);
	ft_term_apply_cmd(cursor->save_cursor_position, 1);
	*pos_y = cursor->pos_y - cursor->y_start;
	ft_term_apply_cmd(cursor->clear_current_line, 1);
	return (EXIT_SUCCESS);
}

/*
** print the down line
*/

int	ft_cusor_clear_down_line(t_cursor *cursor, t_arr *arr)
{
	int				index;
	int				pos_y;
	int				i;

	ft_cusor_clear_down_line_init(cursor, arr, &index, &pos_y);
	if (cursor->y_total > 1)
	{
		ft_term_apply_cmd(cursor->left, cursor->prompt_len);
		ft_term_apply_cmd(cursor->down, 1);
		i = 1;
		while (i < cursor->y_total && i < cursor->terminal_size.ws_row)
		{
			ft_term_apply_cmd(cursor->clear_current_line, 1);
			if (i < cursor->y_total - 1 && i < cursor->terminal_size.ws_row - 1)
				ft_term_apply_cmd(cursor->down, 1);
			i++;
		}
	}
	ft_term_apply_cmd(cursor->restore_cursor_position, 1);
	return (index);
}
