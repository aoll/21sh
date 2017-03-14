/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_is_only_space.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 11:54:08 by alex              #+#    #+#             */
/*   Updated: 2017/02/06 11:54:28 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * check if the charactere are only space
 * if a not space if found return 0
 */
int  ft_parse_is_only_space(t_arr *arr, int index)
{
  char *s_line;

  while (index < (int)arr->length)
  {
    s_line = *(char **)((unsigned char *)arr->ptr + index * arr->sizeof_elem);
    if (!ft_isspace(*s_line))
    {
      return (EXIT_SUCCESS);
    }
    index++;
  }
  return (EXIT_FAILURE);
}
