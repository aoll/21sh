/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:51:21 by alex              #+#    #+#             */
/*   Updated: 2017/03/23 15:09:04 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** checck if the env is present with termcaps and swicth
*/

int	ft_read_parse_cut(t_cursor *cursor, t_list_arr *list_arr)
{
	cursor->is_select = false;
	if (!cursor->is_env)
		return (EXIT_SUCCESS);
	if (list_arr->select_line->length)
	{
		return (ft_cursor_cut(cursor,
			list_arr->arr, list_arr->select_line, &list_arr->copy_line));
	}
	return (EXIT_FAILURE);
}

/*
** checck if the env is present with termcaps and swicth
*/

int	ft_read_parse_copy(t_cursor *cursor, t_list_arr *list_arr)
{
	cursor->is_select = true;
	if (!cursor->is_env)
		return (EXIT_SUCCESS);
	if (list_arr->select_line->length)
	{
		return (ft_cursor_copy_line(
			cursor, list_arr->select_line, &list_arr->copy_line));
	}
	return (EXIT_FAILURE);
}

/*
** return 0 if ctrl-x or ctrl-w or ctrl-v
** else 1
*/

int	ft_read_parse_copy_cut_paste(
	const char *buff, t_cursor *cursor, t_list_arr *list_arr)
{
	if (buff[0] == 24 && !buff[1] && !buff[2] && !buff[3] && !buff[4]
		&& !buff[5] && !buff[6] && !buff[7])
	{
		return (ft_read_parse_cut(cursor, list_arr));
	}
	else if (buff[0] == 23 && !buff[1] && !buff[2] && !buff[3] && !buff[4]
		&& !buff[5] && !buff[6] && !buff[7])
	{
		return (ft_read_parse_copy(cursor, list_arr));
	}
	else if (buff[0] == 22 && !buff[1] && !buff[2] && !buff[3] && !buff[4]
		&& !buff[5] && !buff[6] && !buff[7])
	{
		if (!cursor->is_env)
			return (EXIT_SUCCESS);
		if (list_arr->copy_line->length)
			return (ft_cursor_paste(
				cursor, list_arr->arr, list_arr->copy_line));
	}
	return (EXIT_FAILURE);
}

/*
** is del or suppr return 0
** else return 1
*/

int	ft_read_parse_del_or_suppr(const char *buff, t_cursor *cursor, t_arr *arr)
{
	if (buff[0] == 127 && !buff[1] && !buff[2] && !buff[3] && !buff[4]
		&& !buff[5] && !buff[6] && !buff[7])
	{
		if (cursor->index_line > 0)
		{
			ft_cursor_del_or_suppr(cursor, arr, 1);
		}
		return (EXIT_SUCCESS);
	}
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 51
		&& buff[3] == 126 && !buff[4] && !buff[5] && !buff[6] && !buff[7])
	{
		if (arr->length && cursor->index_line < (int)arr->length)
		{
			ft_cursor_del_or_suppr(cursor, arr, 0);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
** orient in funtion of the pressed key different funtion
*/

int	ft_read_parse(
	const char *buff, t_cursor *cursor, t_list_arr *list_arr)
{
	int				err;
	t_arr			*arr;

	arr = list_arr->arr;
	cursor->is_select = false;
	if (!(err = ft_read_parse_shift(buff, cursor, arr, &list_arr->select_line)))
		return (EXIT_SUCCESS);
	if (!(err = ft_read_parse_ctrl(buff, cursor, arr)))
		return (EXIT_SUCCESS);
	if (!(err = ft_read_parse_arrow(buff, cursor, list_arr)))
		return (EXIT_SUCCESS);
	if (!(err = ft_read_parse_home_end(buff, cursor, arr)))
		return (EXIT_SUCCESS);
	if (!(err = ft_read_parse_ctrl_arrow(buff, cursor, arr)))
		return (EXIT_SUCCESS);
	if (!(err = ft_read_parse_copy_cut_paste(buff, cursor, list_arr)))
		return (EXIT_SUCCESS);
	if (!(err = ft_read_parse_del_or_suppr(buff, cursor, arr)))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
