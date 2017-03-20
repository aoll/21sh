/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_parse_actions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 15:47:41 by alex              #+#    #+#             */
/*   Updated: 2017/03/20 09:14:41 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** function if a key with shift is pressed
** if true return 0 else 1
*/

int	ft_read_parse_shift(
	const char *buff, t_cursor *cursor, t_arr *arr, t_arr **select_line)
{
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
		&& buff[4] == 50 && buff[5] == 68 && !buff[6] && !buff[7])
	{
		cursor->is_select = true;
		if (cursor->index_line > 0 && arr->length && cursor->is_env)
		{
			ft_cursor_select_left(cursor, arr, *select_line);
		}
		return (EXIT_SUCCESS);
	}
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
		&& buff[4] == 50 && buff[5] == 67 && !buff[6] && !buff[7])
	{
		cursor->is_select = true;
		if (cursor->index_line < (int)arr->length && cursor->is_env)
		{
			ft_cursor_select_right(cursor, arr, *select_line);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
** funcion if ctrl-up or ctrl-down is pressed
** true return 0 else return 1
*/

int	ft_read_parse_ctrl(const char *buff, t_cursor *cursor, t_arr *arr)
{
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
		&& buff[4] == 53 && buff[5] == 65 && !buff[6] && !buff[7])
	{
		if (cursor->is_env)
		{
			ft_cursor_up_line(cursor, arr);
		}
		return (EXIT_SUCCESS);
	}
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
		&& buff[4] == 53 && buff[5] == 66 && !buff[6] && !buff[7])
	{
		if (cursor->is_env)
		{
			ft_cursor_down_line(cursor, arr);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
** up or down or key left or right return 0
** else return 1
*/

int	ft_read_parse_arrow(
	const char *buff, t_cursor *cursor, t_list_arr *list_arr)
{
	if (buff[0] == 27 && buff[1] == 91 && (buff[2] == 65 || buff[2] == 66
		|| buff[2] == 67 || buff[2] == 68) && !buff[3] && !buff[4] && !buff[5]
		&& !buff[6] && !buff[7])
	{
		if (buff[2] == 65 && cursor->index_history - 1 >= 0 && cursor->is_env)
			ft_cursor_up_history_line(cursor, list_arr->history_line,
				&list_arr->current_line, &list_arr->arr);
		else if (buff[2] == 66 && cursor->index_history + 1
			< (int)list_arr->history_line->length && cursor->is_env)
			ft_cursor_down_history_line(cursor, list_arr->history_line,
				&list_arr->current_line, &list_arr->arr);
		else if (buff[1] == 91 && buff[2] == 68 && cursor->is_env)
			ft_cursor_left(cursor, list_arr->arr);
		else if (buff[1] == 91 && buff[2] == 67 && cursor->is_env)
			ft_cursor_right(cursor, list_arr->arr);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
** key home or end
*/

int	ft_read_parse_home_end(const char *buff, t_cursor *cursor, t_arr *arr)
{
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 72
		&& !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7])
	{
		if (cursor->is_env)
		{
			ft_cursor_home(cursor, arr);
		}
	}
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 70
		&& !buff[3] && !buff[4] && !buff[5] && !buff[6] && !buff[7])
	{
		if (cursor->is_env)
		{
			ft_cursor_end(cursor, arr);
		}
	}
	else
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
** return 0 if is ctrl-left arrow or ctrl-rigth arrow
*/

int	ft_read_parse_ctrl_arrow(const char *buff, t_cursor *cursor, t_arr *arr)
{
	if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
		&& buff[4] == 53 && buff[5] == 68 && !buff[6] && !buff[7])
	{
		if (cursor->index_line > 0 && cursor->is_env)
		{
			ft_cursor_word_left(cursor, arr);
		}
		return (EXIT_SUCCESS);
	}
	else if (buff[0] == 27 && buff[1] == 91 && buff[2] == 49 && buff[3] == 59
		&& buff[4] == 53 && buff[5] == 67 && !buff[6] && !buff[7])
	{
		if (cursor->index_line < (int)arr->length && cursor->is_env)
		{
			ft_cursor_word_right(cursor, arr);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
