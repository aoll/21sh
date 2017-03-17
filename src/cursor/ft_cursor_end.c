/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 08:47:25 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 08:47:40 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** move the cursor to end of the line even if it's a multi-ligne
*/

int	ft_cursor_end(t_cursor *cursor, t_arr *arr)
{
	while (cursor->index_line != (int)arr->length)
	{
		ft_cursor_right(cursor, arr);
	}
	return (EXIT_SUCCESS);
}
