/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_right_same_line.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:35:20 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 10:35:35 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** next char is on the same line as the cursor
*/

int	ft_cursor_right_same_line(t_cursor *cursor, t_arr *arr,
	unsigned char *s_line)
{
	if (cursor->index_line + 1 == (int)arr->length)
	{
		ft_term_apply_cmd(cursor->right, 1);
		cursor->pos_x++;
		cursor->index_line++;
	}
	else
	{
		if (s_line[4] == 1)
		{
			ft_cursor_right_tab(cursor, 0);
		}
		else
		{
			ft_term_apply_cmd(cursor->right, 1);
			cursor->pos_x++;
			cursor->index_line++;
		}
	}
	return (EXIT_SUCCESS);
}
