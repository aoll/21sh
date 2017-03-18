/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_replace_stderr_double_prev_line.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 11:30:49 by alex              #+#    #+#             */
/*   Updated: 2017/02/06 11:31:41 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_parse_replace_stderr_double_prev_line(
	t_cmd_line *line, char **s_prev_line, char *s_prev_prev_line, t_arr *arr)
{
	if (line->index - 2 < 0)
	{
		**s_prev_line = ' ';
		*line->s_line = D_STDERR_REDIRECT;
		line->index++;
		return (1);
	}
	else
	{
		s_prev_prev_line = *(char **)(
			(unsigned char *)arr->ptr + (line->index - 2) * arr->sizeof_elem);
		if (ft_isspace(*s_prev_prev_line))
		{
			**s_prev_line = ' ';
			*line->s_line = D_STDERR_REDIRECT;
			line->index++;
			return (1);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_parse_replace_stdout_double_prev_line(
	t_cmd_line *line, char **s_prev_line, char *s_prev_prev_line, t_arr *arr)
{
	if (line->index - 2 < 0)
	{
		**s_prev_line = ' ';
		line->index++;
		return (1);
	}
	else
	{
		s_prev_prev_line = *(char **)(
			(unsigned char *)arr->ptr + (line->index - 2) * arr->sizeof_elem);
		if (ft_isspace(*s_prev_prev_line))
		{
			**s_prev_line = ' ';
			line->index++;
			return (1);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_replace_double_stderr_prev_prev_set_line(
	t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line)
{
	*line->s_line = D_STDERR_REDIRECT;
	**s_prev_line = ' ';
	**s_prev_prev_line = ' ';
	line->index++;
	return (1);
}

int	ft_parse_replace_stderr_double_prev_prev_line(
	t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line, t_arr *arr)
{
	char			*s_prev_prev_prev_line;

	if (line->index - 3 < 0)
	{
		return (ft_replace_double_stderr_prev_prev_set_line(
			line, s_prev_line, s_prev_prev_line));
	}
	else
	{
		s_prev_prev_prev_line = *(char **)(
			(unsigned char *)arr->ptr + (line->index - 3) * arr->sizeof_elem);
		if (ft_isspace(*s_prev_prev_prev_line))
		{
			return (ft_replace_double_stderr_prev_prev_set_line(
			 line, s_prev_line, s_prev_prev_line));
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_parse_replace_stdout_double_prev_prev_line(
	t_cmd_line *line, char **s_prev_line, char **s_prev_prev_line, t_arr *arr)
{
	char			*s_prev_prev_prev_line;

	if (line->index - 3 < 0)
	{
		**s_prev_line = ' ';
		**s_prev_prev_line = ' ';
		line->index++;
		return (1);
	}
	else
	{
		s_prev_prev_prev_line = *(char **)(
			(unsigned char *)arr->ptr + (line->index - 3) * arr->sizeof_elem);
		if (ft_isspace(*s_prev_prev_prev_line))
		{
			**s_prev_line = ' ';
			**s_prev_prev_line = ' ';
			line->index++;
			return (1);
		}
	}
	return (EXIT_SUCCESS);
}
