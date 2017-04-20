/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 10:29:20 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 10:32:51 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_read_end(
	t_cursor *cursor, t_list_arr *list_arr, struct termios *term, char **line)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	if (!(ft_read_parse_eof(cursor, list_arr, term, true)))
	{
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
