/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_no_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 10:35:40 by aollivie          #+#    #+#             */
/*   Updated: 2017/05/18 16:41:36 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_check_quote(char c, bool *quote, bool *dquote)
{
	if (c == '"' && !*quote)
	{
		*dquote = !*dquote;
	}
	if (c == '\'' && !*dquote)
	{
		*quote = !*quote;
	}
	return (EXIT_SUCCESS);
}

static bool	ft_check_dquote_quote(char *s)
{
	bool quote;
	bool dquote;

	quote = false;
	dquote = false;
	while (*s)
	{
		ft_check_quote(*s, &quote, &dquote);
		s++;
	}
	if (dquote || quote)
	{
		return (true);
	}
	return (false);
}

int			ft_read_no_env(
	t_cursor *cursor, t_list_arr *list_arr, char **line, struct termios *term)
{
	int rd;

	*line = NULL;
	if (g_is_ctrl_c_father)
	{
		g_is_ctrl_c_father = 0;
		ft_str_free(line);
		return (-1);
	}
	if ((rd = get_next_line(0, line)))
	{
		if (!ft_strcmp(*line, "exit"))
			return (ft_read_end(cursor, list_arr, term, line));
		ft_read_get(cursor, list_arr, line, ft_check_dquote_quote(*line));
	}
	else if (!*line)
	{
		return (ft_read_end(cursor, list_arr, term, line));
	}
	if (!rd)
		return (ft_read_end(cursor, list_arr, term, line));
	if (*line)
		ft_str_free(line);
	return (1);
}
