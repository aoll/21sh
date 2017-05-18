/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_replace_sdterr_redirect.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 08:45:05 by alex              #+#    #+#             */
/*   Updated: 2017/05/18 17:55:43 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** replace all 2> and 2&> outside quote and dquote
*/

static int	ft_replace_redirect_and(
	t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line, t_arr *arr)
{
	if (line->index - 2 >= 0)
	{
		*s_prev_prev_line = *(char **)(
			(unsigned char *)arr->ptr + (line->index - 2) * arr->sizeof_elem);
		if (**s_prev_prev_line == '2'
		&& ft_parse_replace_prev_prev_line_stderr(
			line, s_prev_line, s_prev_prev_line, arr))
		{
			return (1);
		}
		if (**s_prev_prev_line == '1'
		&& ft_parse_replace_prev_prev_line_stdout(
				line, s_prev_line, s_prev_prev_line, arr))
		{
			return (1);
		}
	}
	return (EXIT_SUCCESS);
}

static int	ft_parse_replace_sdterr_redirect_switch(
	t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line, t_arr *arr)
{
	if (**s_prev_line == '2' && ft_parse_replace_prev_line_stderr(
		line, s_prev_line, *s_prev_prev_line, arr))
	{
		return (1);
	}
	if (**s_prev_line == '1' && ft_parse_replace_prev_line_stdout(
		line, s_prev_line, *s_prev_prev_line, arr))
	{
		return (1);
	}
	if (**s_prev_line == '&' && ft_replace_redirect_and(
		line, s_prev_line, s_prev_prev_line, arr))
	{
		return (1);
	}
	return (EXIT_SUCCESS);
}

int			ft_parse_replace_sdterr_redirect(t_arr *arr)
{
	char			*s_prev_line;
	char			*s_prev_prev_line;
	t_cmd_line		line;

	ft_parse_init_cmd_line(&line);
	while (line.index < (int)arr->length)
	{
		line.s_line = *(char **)(
			(unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
		ft_parse_check_d_quote(&line);
		if (!line.dquote && !line.quote
			&& *line.s_line == S_RIGHT_REDIRECT && line.index - 1 >= 0)
		{
			s_prev_line = *(char **)((unsigned char *)arr->ptr
			+ (line.index - 1) * arr->sizeof_elem);
			if (ft_parse_replace_sdterr_redirect_switch(
				&line, &s_prev_line, &s_prev_prev_line, arr))
				continue;
		}
		line.index++;
	}
	return (EXIT_SUCCESS);
}
