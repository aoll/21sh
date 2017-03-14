/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_word_right.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 12:48:30 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 12:48:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * move the cursor to the begin of a word if the actual position is on a space
 * is_on_words = 0
 * or
 * move the cursor to the end of a word if the actual position is on a word
 * is_on_words = 1
 */
int  ft_cursor_move_begin_or_start(t_cursor *cursor, t_arr *arr,
  unsigned char *s_line, int is_on_words)
{
  while (cursor->index_line < (int)arr->length
  && (ft_isspace(*(s_line)) == is_on_words))
  {
    int err;

    if ((err = ft_cursor_right(cursor, arr)))
    {
      return (EXIT_FAILURE);
    }
    if (cursor->index_line == (int)arr->length)
    {
      return (EXIT_SUCCESS);
    }
    s_line  = (unsigned char *)arr->ptr + arr->sizeof_elem
    * (cursor->index_line);
    s_line = *(unsigned char **)s_line;
  }
  return (EXIT_SUCCESS);
}

/*
 * move the cursor words to words to the right direction
 * if the cursor position is on a space move the cursor
 * on the first char (begin of the word)
 * else if the cursor is on a char and is not a space
 * move to the end of the word
 */
int  ft_cursor_word_right(t_cursor *cursor, t_arr *arr)
{
  unsigned char *s_line;

  if (!cursor)
  {
    return (EXIT_FAILURE);
  }
  s_line  = (unsigned char *)arr->ptr + arr->sizeof_elem * (cursor->index_line);
  s_line = *(unsigned char **)s_line;
  ft_cursor_move_begin_or_start(cursor, arr, s_line, ft_isspace(*s_line));

  return (EXIT_SUCCESS);
}
