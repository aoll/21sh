/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_valide_line_with_line.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 12:30:04 by alex              #+#    #+#             */
/*   Updated: 2017/03/12 12:32:04 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_cursor_valide_line_with_line(
	t_arr *tmp_arr, t_arr *tmp_current_line, t_arr *tmp_history_line)
{
	t_arr			*invalide_line;

	ft_arr_push(tmp_current_line, ft_arr_dup(tmp_arr), -1);
	invalide_line = *(t_arr **)((unsigned char *)tmp_history_line->ptr
	+ (tmp_history_line->length - 1) * tmp_history_line->sizeof_elem);
	if (invalide_line->length < 2)
	{
		ft_arr_free(ft_arr_pop(invalide_line, 0));
		ft_arr_free(ft_arr_pop(tmp_history_line, tmp_history_line->length - 1));
	}
	return (EXIT_SUCCESS);
}
