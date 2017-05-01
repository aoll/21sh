/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_del_char_check_quote_is_inside.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:01:33 by alex              #+#    #+#             */
/*   Updated: 2017/05/01 12:02:03 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** check if quote or duote is pair after the index position
*/

static bool	ft_arr_del_char_check_quote_after(
	t_cursor *cursor, t_arr *arr, char c_quote, int index_line_tmp)
{
	char *char_line;
	int index;
	int c_after;

	c_after = 0;
	index = index_line_tmp;
	while (index < (int)arr->length)
	{
		char_line = *((char **)(
			(unsigned char *)arr->ptr + arr->sizeof_elem * index));
		if (*char_line == c_quote)
		{
			c_after++;
		}
		index++;
	}
	if (c_after > 0 && c_after % 2 > 0)
	{
		return (true);
	}
	return (false);
}

/*
** check if quote or duote is pair before the index position
*/

static bool	ft_arr_del_char_check_quote_before(
	t_cursor *cursor, t_arr *arr, char c_quote, int index_line_tmp)
{
	char *char_line;
	int index;
	int c_before;

	c_before = 0;
	index = index_line_tmp;
	while (index >= 0)
	{
		char_line = *(char **)(
			(unsigned char *)arr->ptr + arr->sizeof_elem * index);
		if (*char_line == c_quote)
		{
			c_before++;
		}
		index--;
	}
	if (c_before > 0 && c_before % 2 > 0)
	{
		return (true);
	}
	return (false);
}

/*
** check if the new quote is inside quote or dquote
*/

int	ft_arr_del_char_check_quote_is_inside(
	t_cursor *cursor, t_arr *arr, char c_quote, int index_line_tmp)
{
	if (ft_arr_del_char_check_quote_before(cursor, arr, c_quote, index_line_tmp) &&
	ft_arr_del_char_check_quote_after(cursor, arr, c_quote, index_line_tmp))
	{
			return (true);
	}
	return (false);
}
