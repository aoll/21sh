/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pop_space_inside.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:00:49 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 19:10:39 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** pop usless space outside quote or dquote
*/

static int	ft_parse_pop_space_or_continue(t_cmd_line *line, t_arr *arr)
{
	if (line->index + 1 < (int)arr->length)
	{
		line->s_line = *(char **)(
			(unsigned char *)arr->ptr + (line->index + 1) * arr->sizeof_elem);
		if (ft_isspace(*line->s_line))
		{
			free(ft_arr_pop(arr, line->index));
		}
		else
		{
			line->index++;
		}
	}
	else
	{
		free(ft_arr_pop(arr, line->index));
	}
	return (EXIT_SUCCESS);
}

int	ft_parse_pop_space_inside(t_arr *arr)
{
	t_cmd_line		line;

	ft_parse_init_cmd_line(&line);
	while (line.index < (int)arr->length)
	{
		line.s_line = *(char **)(
			(unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
		ft_parse_check_d_quote(&line);
		if (!line.quote && !line.dquote && ft_isspace(*line.s_line))
		{
			ft_parse_pop_space_or_continue(&line, arr);
		}
		else
		{
			line.index++;
		}
	}
	return (EXIT_SUCCESS);
}
