/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_valide_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:20:46 by alex              #+#    #+#             */
/*   Updated: 2017/03/12 12:31:52 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int	ft_cursor_valide_line_second_line(
	t_arr *tmp_arr, t_arr *tmp_current_line, t_arr *tmp_history_line)
{
	t_arr			*invalide_line;
	t_arr			*line_tmp;

	invalide_line = *(t_arr **)((unsigned char *)tmp_history_line->ptr
	+ (tmp_history_line->length - 1) * tmp_history_line->sizeof_elem);
	if (invalide_line->length < 2)
	{
		ft_arr_free(ft_arr_pop(invalide_line, 0));
		ft_arr_free(ft_arr_pop(tmp_history_line, tmp_history_line->length - 1));
	}
	line_tmp = ft_arr_new(2, sizeof(t_arr *));
	ft_arr_push(line_tmp, ft_arr_dup(tmp_arr), 0);
	ft_arr_push(line_tmp, ft_arr_dup(tmp_arr), 1);
	ft_arr_push(tmp_history_line, line_tmp, -1);
	ft_arr_free(ft_arr_pop(tmp_current_line, 1));
	tmp_arr = *(t_arr **)tmp_current_line->ptr;
	ft_arr_push(tmp_current_line, ft_arr_dup(tmp_arr), 1);
	return (EXIT_SUCCESS);
}

int	ft_cursor_valide_line_second_without_line(t_arr *tmp_history_line)
{
	t_arr			*invalide_line;

	invalide_line = *(t_arr **)((unsigned char *)tmp_history_line->ptr
	+ (tmp_history_line->length - 1) * tmp_history_line->sizeof_elem);
	if (invalide_line->length < 2)
	{
		ft_arr_free(ft_arr_pop(invalide_line, 0));
		ft_arr_free(ft_arr_pop(tmp_history_line, tmp_history_line->length - 1));
	}
	return (EXIT_SUCCESS);
}

int	ft_cursor_valide_line_free(
	t_cursor *cursor, t_arr *tmp_arr, t_arr *tmp_history_line)
{
	t_arr			*line_tmp;

	cursor->index_history = 0;
	while (cursor->index_history < (int)tmp_history_line->length)
	{
		line_tmp = *(t_arr **)((unsigned char *)tmp_history_line->ptr
		+ cursor->index_history * tmp_history_line->sizeof_elem);
		ft_arr_free(ft_arr_pop(line_tmp, 1));
		tmp_arr = *(t_arr **)line_tmp->ptr;
		tmp_arr = ft_arr_dup(tmp_arr);
		if (tmp_arr)
		{
			ft_arr_push(line_tmp, tmp_arr, 1);
		}
		cursor->index_history++;
	}
	return (EXIT_SUCCESS);
}

int	ft_cursor_valide_line_switch(
	t_arr *tmp_arr, t_arr *tmp_current_line, t_arr *tmp_history_line)
{
	if (tmp_current_line->length == 1 && tmp_arr->length)
	{
		ft_cursor_valide_line_with_line(
			tmp_arr, tmp_current_line, tmp_history_line);
	}
	else if (tmp_current_line->length == 1 && !tmp_arr->length)
	{
		ft_cursor_valide_line_without_line(tmp_history_line);
	}
	else if (tmp_current_line->length >= 2 && tmp_arr->length)
	{
		ft_cursor_valide_line_second_line(
			tmp_arr, tmp_current_line, tmp_history_line);
	}
	else if (tmp_current_line->length >= 2 && !tmp_arr->length)
	{
		ft_cursor_valide_line_second_without_line(tmp_history_line);
	}
	return (EXIT_SUCCESS);
}

/*
** add the current_line to the history_line (history command)
** exec the current_line
** show a new prompt
*/

int	ft_cursor_valide_line(
	t_cursor *cursor, t_arr **history_line, t_arr **current_line, t_arr **arr)
{
	t_arr			*tmp_arr;
	t_arr			*tmp_current_line;
	t_arr			*tmp_history_line;

	tmp_arr = *arr;
	tmp_current_line = *current_line;
	tmp_history_line = *history_line;
	ft_cursor_end(cursor, tmp_arr);
	ft_cursor_valide_line_switch(tmp_arr, tmp_current_line, tmp_history_line);
	ft_cursor_valide_line_free(cursor, tmp_arr, tmp_history_line);
	tmp_arr = ft_arr_new(1, sizeof(char*));
	tmp_arr->f_print = &ft_arr_putchar;
	tmp_arr->f_dup_elem = &ft_arr_strdup;
	tmp_current_line = ft_arr_new(1, sizeof(t_arr*));
	ft_arr_push(tmp_current_line, tmp_arr, 0);
	ft_arr_push(tmp_history_line, tmp_current_line, -1);
	ft_cursor_valide_line_init_cursor_prompt(
		cursor, tmp_history_line->length - 1);
	*arr = tmp_arr;
	*current_line = tmp_current_line;
	*history_line = tmp_history_line;
	return (EXIT_SUCCESS);
}
