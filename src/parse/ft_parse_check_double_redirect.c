/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_check_double_redirect.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 20:03:35 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 20:07:07 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * check if duble & exist outside quote and dquote
 * return 1 if is true
 */
int  ft_parse_check_double_redirect(t_arr *arr)
{
  t_cmd_line line;

  ft_parse_init_cmd_line(&line);
  while (line.index < (int)arr->length)
  {
    line.s_line = *(char **)(
      (unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
    ft_parse_check_d_quote(&line);
    if (!line.dquote && !line.quote && *line.s_line == '&')
    {
      if (line.index + 1 < (int)arr->length)
      {
        line.s_line = *(char **)(
          (unsigned char *)arr->ptr + (line.index + 1) * arr->sizeof_elem);
        if (*line.s_line == '&')
          return (EXIT_FAILURE);
      }
    }
    line.index++;
  }
  return (EXIT_SUCCESS);
}
