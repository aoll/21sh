/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pop_prev_space.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:14:05 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 19:15:07 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * pop usles space on the begin of the command
 */
int  ft_parse_pop_prev_space(t_arr *arr)
{
  int index;
  char *s_line;

  index = 0;
  while (index < (int)arr->length)
  {
    s_line = *(char **)((unsigned char *)arr->ptr + index * arr->sizeof_elem);
    if (!ft_isspace(*s_line))
    {
      return (EXIT_SUCCESS);
    }
    else
    {
      free(ft_arr_pop(arr, 0));
    }
  }
  return (EXIT_SUCCESS);
}
