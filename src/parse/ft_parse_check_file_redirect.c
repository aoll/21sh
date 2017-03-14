/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_check_file_redirect.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:02:21 by alex              #+#    #+#             */
/*   Updated: 2017/02/06 12:16:14 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * check if a token is not the end of the command (space not included)
 * return 1 if is true or 0 if not
 */

static int  ft_parse_check_file_redirect_check_end_line(
  t_cmd_line *line, t_arr *arr)
{
  if (line->index + 1 < (int)arr->length)
  {
    line->s_line = *(char **)(
      (unsigned char *)arr->ptr + (line->index + 1) * arr->sizeof_elem);
    if (*line->s_line == D_LEFT_REDIRECT)
    {
      ft_putstr_fd("\n21sh: parse error near `>'", STDERR);
      return (EXIT_FAILURE);
    }
    if (ft_isspace(*line->s_line))
    {
      ft_putstr_fd("\n21sh: parse error near `&'", STDERR);
      return (EXIT_FAILURE);
    }
  }
  else
  {
    ft_putstr_fd("\n21sh: parse error near `\\n'", STDERR);
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}


static int  ft_parse_check_file_redirect_switch(t_cmd_line *line, t_arr *arr)
{
  int err;

  if (!line->dquote && !line->quote)
  {
    if (*line->s_line == FILE_REDIRECT)
    {
      if ((err = ft_parse_check_file_redirect_check_end_line(line, arr)))
      {
        return (EXIT_FAILURE);
      }
      if (line->index - 1 >= 0)
      {
        line->s_line = *(char **)(
          (unsigned char *)arr->ptr + (line->index - 1) * arr->sizeof_elem);
        if (ft_isspace(*line->s_line))
        {
          ft_putstr_fd("\n21sh: parse error near `&'", STDERR);
          return (EXIT_FAILURE);
        }
      }
    }
  }
  return (EXIT_SUCCESS);
}

int  ft_parse_check_file_redirect(t_arr *arr)
{
  t_cmd_line line;
  int err;

  ft_parse_init_cmd_line(&line);
  while (line.index < (int)arr->length)
  {
    line.s_line = *(char **)(
      (unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
    ft_parse_check_d_quote(&line);
    if ((err = ft_parse_check_file_redirect_switch(&line, arr)))
    {
      return (EXIT_FAILURE);
    }
    line.index++;
  }
  return (EXIT_SUCCESS);
}
