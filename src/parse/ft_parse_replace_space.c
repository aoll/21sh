/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_replace_space.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:20:53 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 19:26:23 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * replace space outside quote or dquote
 */
int  ft_parse_replace_space(t_arr *arr)
{
  t_cmd_line line;

  ft_parse_init_cmd_line(&line);
  while (line.index < (int)arr->length)
  {
    line.s_line = *(char **)(
      (unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
    ft_parse_check_d_quote(&line);
    if (!line.quote && !line.dquote && ft_isspace(*line.s_line))
    {
      *line.s_line = SPACE_SEPARATOR;
    }
    line.index++;
  }
  return (EXIT_SUCCESS);
}
