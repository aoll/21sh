/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_no_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 10:35:40 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 10:41:34 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_read_no_env(
	t_cursor *cursor, t_list_arr *list_arr, char **line, struct termios *term)
{
	*line = NULL;
	if (g_is_ctrl_c_father)
	{
		g_is_ctrl_c_father = 0;
		ft_str_free(line);
		return (-1);
	}
	if (get_next_line(0, line))
	{
		ft_read_get(cursor, list_arr, line);
	}
	else
	{
		return (ft_read_end(cursor, list_arr, term, line));
	}
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (1);
}
