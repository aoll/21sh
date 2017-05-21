/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 16:59:19 by alex              #+#    #+#             */
/*   Updated: 2017/05/21 19:22:37 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_read_exit(t_list_arr *list_arr, t_cursor *cursor, struct termios *term)
{
	if (list_arr->tab_cmds)
	{
		while (list_arr->tab_cmds->length)
		{
			ft_arr_free(ft_arr_pop(list_arr->tab_cmds, 0));
		}
		if (list_arr->tab_cmds->ptr)
		{
			free(list_arr->tab_cmds->ptr);
		}
		free(list_arr->tab_cmds);
		list_arr->tab_cmds = NULL;
	}
	ft_read_parse_eof(cursor, list_arr, term, true);
	return (EXIT_SUCCESS);
}
