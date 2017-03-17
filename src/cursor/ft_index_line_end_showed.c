/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_line_end_showed.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:36:46 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 10:37:04 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"
/*
** return the index of the last char print with line + 1
*/

int	ft_index_line_end_showed(t_cursor *cursor, t_arr *arr)
{
	int				index;
	unsigned char	*s_line;
	int				index_line;

	index = cursor->index_line + 1; // not sure
	index_line = 0;
	while (index < (int)arr->length)
	{
		s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * index;
		s_line = *(unsigned char **)s_line;
		if (index_line == cursor->terminal_size.ws_col - 1 || *s_line == 10)
		{
			if (*s_line == 10)
			{
			 return (index - 1);
			}
			return (index);
		}
		index_line++;
		index++;
	}
	return (index - 1);
}
