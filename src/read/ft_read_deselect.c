/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_deselect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:50:45 by alex              #+#    #+#             */
/*   Updated: 2017/04/19 16:50:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_read_deselect(t_list_arr *list_arr, t_cursor *cursor)
{
	ft_bzero(list_arr->buff, 8);
	if (!cursor->is_select
		&& list_arr->select_line->length && list_arr->arr->length)
	{
		ft_cursor_deselect_all(cursor, list_arr->arr, list_arr->select_line);
	}
	return (EXIT_SUCCESS);
}
