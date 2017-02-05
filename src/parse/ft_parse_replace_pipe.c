/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_replace_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:56:44 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 19:58:33 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * replace all pipe outside quote and dquote
 */
int  ft_parse_replace_pipe(t_arr *arr)
{
  t_cmd_line line;

  ft_parse_init_cmd_line(&line);
  while (line.index < (int)arr->length)
  {
    line.s_line = *(char **)(
      (unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
    ft_parse_check_d_quote(&line);
    if (!line.dquote && !line.quote && *line.s_line == '|')
    {
      *line.s_line = PIPE;
    }
    line.index++;
  }
  return (EXIT_SUCCESS);
}
