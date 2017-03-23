/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_valide_line_without_line.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 12:29:25 by alex              #+#    #+#             */
/*   Updated: 2017/03/12 12:29:50 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_cursor_valide_line_without_line(t_arr *tmp_history_line)
{
	t_arr			*invalide_line;

	invalide_line = *(t_arr **)((unsigned char *)tmp_history_line->ptr
	+ (tmp_history_line->length - 1) * tmp_history_line->sizeof_elem);
	if (invalide_line->length < 2)
	{
		ft_arr_free(ft_arr_pop(invalide_line, 0));
		ft_arr_free(ft_arr_pop(tmp_history_line, tmp_history_line->length - 1));
	}
	return (EXIT_SUCCESS);
}
