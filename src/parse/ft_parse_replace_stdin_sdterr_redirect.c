/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_replace_stdin_sdterr_redirect.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 20:08:25 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 20:53:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * replace all &> outside quote and dquote
 */

static int  ft_parse_replace_in_line(t_cmd_line *line, t_arr *arr)
{
  if (line->index + 1 < (int)arr->length)
  {
    line->s_line = *(char **)(
      (unsigned char *)arr->ptr + (line->index + 1) * arr->sizeof_elem);
    if (*line->s_line == S_RIGHT_REDIRECT)
    {
      *line->s_line = STDOUT_STDERR_REDIRECT;
      line->s_line = *(char **)(
        (unsigned char *)arr->ptr + (line->index ) * arr->sizeof_elem);
      *line->s_line = ' ';
      line->index++;
      return (1);
    }
  }
  return (EXIT_SUCCESS);
}

int  ft_parse_replace_stdin_sdterr_redirect(t_arr *arr)
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
      *line.s_line = FILE_REDIRECT;
      if (ft_parse_replace_in_line(&line, arr))
      {
        continue;
      }
    }
    line.index++;
  }
  return (EXIT_SUCCESS);
}
