/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 10:44:17 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:03:39 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	ft_read_env_deselect(t_cursor *cursor, t_list_arr *list_arr)
{
	if (!cursor->is_select && list_arr->select_line->length
		&& list_arr->arr->length)
	{
		ft_cursor_deselect_all(cursor, list_arr->arr, list_arr->select_line);
	}
	ft_bzero(list_arr->buff, 8);
	return (EXIT_SUCCESS);
}

static bool	ft_read_env_is_enter(t_cursor *cursor, t_list_arr *list_arr)
{
	if ((!cursor->dquote && !cursor->quote && list_arr->buff[0] == 10
		&& !list_arr->buff[1] && !list_arr->buff[2] && !list_arr->buff[3]
		&& !list_arr->buff[4] && !list_arr->buff[5] && !list_arr->buff[6]
		&& !list_arr->buff[7]))
	{
		return (true);
	}
	return (false);
}

static int	ft_read_env_switch(
	t_cursor *cursor, t_list_arr *list_arr, struct termios *term)
{
	int err;

	cursor->is_select = false;
	if (!(ft_read_parse((const char *)list_arr->buff, cursor, list_arr)))
	{
		ft_read_deselect(list_arr, cursor);
		return (-1);
	}
	else if (!(ft_read_parse_eof(cursor, list_arr, term, false)))
	{
		return (EXIT_SUCCESS);
	}
	else if (ft_read_env_is_enter(cursor, list_arr))
	{
		if ((err = ft_read_exec(cursor, list_arr, term)) != -1)
			return (err);
	}
	else
	{
		ft_cursor_add_char(cursor, list_arr->arr, list_arr->buff);
	}
	return (-2);
}

int	ft_read_env(t_cursor *cursor, t_list_arr *list_arr, struct termios *term)
{
	int rd;
	int err;

	if ((rd = read(0, list_arr->buff, 8)) > 0)
	{
		if ((err = ft_read_env_switch(cursor, list_arr, term)) != -2)
		{
			return (err);
		}
		ft_read_env_deselect(cursor, list_arr);
	}
	return (-2);
}
