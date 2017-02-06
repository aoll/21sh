/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_check_end_space.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 11:55:56 by alex              #+#    #+#             */
/*   Updated: 2017/02/06 11:57:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * check if a token is not the end of the command (space not included)
 * return 1 if is true or 0 if not
 */
int  ft_parse_check_end_space(t_arr *arr)
{
  t_cmd_line line;

  ft_parse_init_cmd_line(&line);
  while (line.index < (int)arr->length)
  {
    line.s_line = *(char **)(
      (unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
    ft_parse_check_d_quote(&line);
    if (!line.dquote && !line.quote)
    {
      if (*line.s_line == D_LEFT_REDIRECT || *line.s_line == D_RIGHT_REDIRECT
      || *line.s_line == S_LEFT_REDIRECT || *line.s_line == S_RIGHT_REDIRECT
      || *line.s_line == PIPE || *line.s_line == STDOUT_STDERR_REDIRECT
      || *line.s_line == STDERR_REDIRECT || *line.s_line == D_STDERR_REDIRECT)
      {
        if (ft_parse_is_only_space(arr, line.index + 1))
          return (EXIT_FAILURE);
      }
    }
    line.index++;
  }
  return (EXIT_SUCCESS);
}
