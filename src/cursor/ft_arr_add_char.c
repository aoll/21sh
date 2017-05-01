/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_add_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:51:54 by aollivie          #+#    #+#             */
/*   Updated: 2017/05/01 11:15:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** check if quote or duote is pair after the index position
*/

static bool	ft_arr_add_char_check_quote_after(
	t_cursor *cursor, t_arr *arr, char c_quote)
{
	char *char_line;
	int index;
	int c_after;

	c_after = 0;
	index = cursor->index_line;
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

static bool	ft_arr_add_char_check_quote_before(
	t_cursor *cursor, t_arr *arr, char c_quote)
{
	char *char_line;
	int index;
	int c_before;

	c_before = 0;
	index = cursor->index_line - 1;
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

int	ft_arr_add_char_check_quote_is_inside(
	t_cursor *cursor, t_arr *arr, char c_quote)
{
	if (ft_arr_add_char_check_quote_before(cursor, arr, c_quote) &&
	ft_arr_add_char_check_quote_after(cursor, arr, c_quote))
	{
			return (true);
	}
	return (false);
}

/*
** add a char to arr a marke if is a element to a tabulation
*/

int	ft_arr_add_char(t_cursor *cursor, t_arr *arr, char c, int is_tab)
{
	char	*char_line;

	if (c == '"' && !cursor->quote
	&& !ft_arr_add_char_check_quote_is_inside(cursor, arr, '\''))
	{
		cursor->dquote = !cursor->dquote;
	}
	if (c == '\'' && !cursor->dquote
	&& !ft_arr_add_char_check_quote_is_inside(cursor, arr, '"'))
	{
		cursor->quote = !cursor->quote;
	}
	char_line = ft_strnew(8);
	ft_bzero(char_line, 8);
	*char_line = c;
	char_line[4] = is_tab;
	ft_arr_push(arr, char_line, cursor->index_line);
	cursor->index_line++;
	return (EXIT_SUCCESS);
}
