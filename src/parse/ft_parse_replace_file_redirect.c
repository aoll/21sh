/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_replace_file_redirect.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 20:00:51 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 20:01:53 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * replace all & outside quote and dquote
 */
int  ft_parse_replace_file_redirect(t_arr *arr)
{
  t_cmd_line line;

  ft_parse_init_cmd_line(&line);
  while (line.index < (int)arr->length)
  {
    line.s_line = *(char **)((unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
    ft_parse_check_d_quote(&line);
    if (!line.dquote && !line.quote && *line.s_line == '&')
    {
      *line.s_line = FILE_REDIRECT;
    }
    line.index++;
  }
  return (EXIT_SUCCESS);
}
