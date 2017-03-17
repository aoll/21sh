/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_word_left.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:48:00 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 12:48:18 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** loop for move the cursor to the begin of a word if the cursor is on a word
** and not on the begining is_on_words = 1;
** or
** for move the cursor to the end of a word if the cursor is already on the
** begining off a word or on a space
*/

static int	ft_cursor_move_word(t_cursor *cursor, t_arr *arr,
	unsigned char *s_line, int is_on_words)
{
	int				err;

	while (cursor->index_line && ft_isspace(*s_line) == is_on_words)
	{
		if ((err = ft_cursor_left(cursor, arr)))
		{
			return (EXIT_FAILURE);
		}
		if (cursor->index_line - 1 < 0)
		{
			break;
		}
		s_line = (unsigned char *)arr->ptr + arr->sizeof_elem *
		(cursor->index_line - 1);
		s_line = *(unsigned char **)s_line;
	}
	return (EXIT_SUCCESS);
}

/*
** move the cursor word to word on the left direction
** if the cursor position is on a space move the cursor
** on the last space before of the last char of a word (end of the word)
** else if the cursor is on a char and is not a space
** move to the beginig of the word
*/

int	ft_cursor_word_left(t_cursor *cursor, t_arr *arr)
{
	unsigned char	*s_line;

	if (!cursor || !arr || cursor->index_line <= 0)
	{
		return (EXIT_FAILURE);
	}
	if (cursor->index_line - 1 >= 0)
	{
		s_line = (unsigned char *)arr->ptr + arr->sizeof_elem *
		(cursor->index_line - 1);
		s_line = *(unsigned char **)s_line;
		ft_cursor_move_word(cursor, arr, s_line, ft_isspace(*s_line));
	}
	return (EXIT_SUCCESS);
}
