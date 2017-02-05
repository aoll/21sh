/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_replace_s_right_redirect.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:48:41 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 19:50:17 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * replace all simple right redirection outside quote and dquote
 */
int  ft_parse_replace_s_right_redirect(t_arr *arr)
{
  t_cmd_line line;

  ft_parse_init_cmd_line(&line);
  while (line.index < (int)arr->length)
  {
    line.s_line = *(char **)(
      (unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
    ft_parse_check_d_quote(&line);
    if (!line.dquote && !line.quote && *line.s_line == '>')
    {
      *line.s_line = S_RIGHT_REDIRECT;
    }
    line.index++;
  }
  return (EXIT_SUCCESS);
}
