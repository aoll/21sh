/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:41:01 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:41:04 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** check if resize is needed and if a ctrl-c is type
*/

int	ft_check_loop(
	struct winsize *terminal_size_old, t_cursor *cursor, t_list_arr *list_arr)
{
	ft_terminal_winsize(terminal_size_old);
	if (cursor->terminal_size.ws_col != terminal_size_old->ws_col
		|| cursor->terminal_size.ws_row != terminal_size_old->ws_row)
	{
		ft_cursor_resize(cursor, list_arr->arr, terminal_size_old);
	}
	if (g_is_ctrl_c_father)
	{
		if (cursor->is_env)
		{
			ft_read_ctrl_c_env(cursor, list_arr->arr);
			ft_cursor_valide_line(cursor, &list_arr->history_line,
				&list_arr->current_line, &list_arr->arr);
			ft_bzero(list_arr->buff, 8);
			return (1);
		}
	}
	return (EXIT_SUCCESS);
}
