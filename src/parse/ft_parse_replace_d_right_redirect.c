/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_replace_d_right_redirect.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:41:16 by alex              #+#    #+#             */
/*   Updated: 2017/03/18 10:30:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** replace all double right redirection outside quote and dquote
*/

static int	ft_parse_replace_d_right_redirect_line(
		t_cmd_line *line, t_arr *arr)
{
		if (!line->dquote && !line->quote)
		{
			if (*line->s_line == '>' && line->index + 1 < (int)arr->length)
			{
				line->s_line = *(char **)((unsigned char *)arr->ptr
				+ (line->index + 1) * arr->sizeof_elem);
				if (*line->s_line == '>')
				{
					free(ft_arr_pop(arr, line->index));
					*line->s_line = D_RIGHT_REDIRECT;
				}
			}
		}
		return (EXIT_SUCCESS);
}

int	ft_parse_replace_d_right_redirect(t_arr *arr)
{
	t_cmd_line		line;

	ft_parse_init_cmd_line(&line);
	while (line.index < (int)arr->length)
	{
		line.s_line = *(char **)(
			(unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
		ft_parse_check_d_quote(&line);
		ft_parse_replace_d_right_redirect_line(&line, arr);
		line.index++;
	}
	return (EXIT_SUCCESS);
}
