/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_copy_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 18:06:33 by alex              #+#    #+#             */
/*   Updated: 2017/03/12 18:06:34 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * free the old the copy line and return a new fresh copy from select_line
 */
int  ft_cursor_copy_line(
  t_cursor *cursor, t_arr *select_line, t_arr **copy_line)
{
  cursor->is_select = true;
  if (select_line->length)
  {
    if (*copy_line)
    {
      ft_arr_free(*copy_line);
      *copy_line = NULL;
    }
    *copy_line = ft_arr_dup(select_line);
  }
  return (EXIT_SUCCESS);
}
