/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 08:47:35 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 08:47:38 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * move the cursor of the begin of the line even if it's a multiple line
 */
int  ft_cursor_home(t_cursor *cursor, t_arr *arr)
{
  if (!cursor->up || !cursor->move_x)
  {
    return (EXIT_FAILURE);
  }
  while (cursor->index_line)
  {
    ft_cursor_left(cursor, arr);
  }
  return (EXIT_SUCCESS);
}
