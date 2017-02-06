/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_separate_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 12:34:16 by alex              #+#    #+#             */
/*   Updated: 2017/02/06 15:29:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * separate the line on a multiple line whitout "free ;" (; not inside quote or
 * dquote)
 * return null if line lenght == 0
 */
static int  ft_parse_separate_cmd_push_new(t_arr **tab_cmds, t_arr **cmd)
{
  ft_parse_init_new_arr_line(cmd);
  ft_arr_push(tab_cmds, *cmd, -1);
  return (EXIT_SUCCESS);
}

static int  ft_parse_separate_cmd_is_new_cmd(
  t_cmd_line *line, t_arr **tab_cmds, t_arr **cmd, t_arr *arr)
{
  if (*line->s_line == ';' && !line->dquote && !line->quote
  && line->index + 1 < (int)arr->length)
  {
    if ((*cmd)->length)
    {
      ft_parse_separate_cmd_push_new(tab_cmds, cmd);
    }
  }
  else if (*line->s_line != ';')
  {
    ft_arr_push(cmd, ft_strdup((const char *)line->s_line), -1);
  }
  return (EXIT_SUCCESS);
}

t_arr  *ft_parse_separate_cmd(t_arr *arr)
{
  t_arr *tab_cmds;
  t_arr *cmd;
  t_cmd_line line;

  if (!arr->length)
  {
    return (NULL);
  }
  ft_parse_init_cmd_line(&line);
  tab_cmds = ft_arr_new(1, sizeof(t_arr *));
  ft_parse_separate_cmd_push_new(&tab_cmds, &cmd);
  while (line.index < (int)arr->length)
  {
    line.s_line = *(char **)(
      (unsigned char *)arr->ptr + line.index * arr->sizeof_elem);
    ft_parse_check_d_quote(&line);
    ft_parse_separate_cmd_is_new_cmd(&line, &tab_cmds, &cmd, arr);
    line.index++;
  }
  return (tab_cmds);
}
