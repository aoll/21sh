/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pop_and_replace_and_check_error.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:26:16 by alex              #+#    #+#             */
/*   Updated: 2017/02/06 12:31:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * itere every line and aply function who pop every usless space
 * replace char by token
 * check error
 */
static int  ft_parse_replace_by_token(t_arr *cmd)
{
  ft_parse_pop_prev_space(cmd);
  ft_parse_pop_space_inside(cmd);
  ft_parse_replace_d_left_redirect(cmd);
  ft_parse_replace_d_right_redirect(cmd);
  ft_parse_replace_s_left_redirect(cmd);
  ft_parse_replace_s_right_redirect(cmd);
  ft_parse_replace_pipe(cmd);
  return (EXIT_SUCCESS);
}

static int  ft_parse_replace_double_by_token(t_arr *cmd)
{
  ft_parse_replace_sdterr_redirect(cmd);
  ft_parse_replace_sdterr_double_redirect(cmd);
  ft_parse_replace_stdin_sdterr_redirect(cmd);
  ft_parse_replace_file_redirect(cmd);
  return (EXIT_SUCCESS);
}

static int  ft_parse_pop_and_replace_and_check_error_switch(t_arr *cmd)
{
  int err;

  ft_parse_replace_by_token(cmd);
  if ((err = ft_parse_check_double_redirect(cmd)))
  {
    ft_putstr_fd("\n21sh: parse error near `&'", STDERR);
    return (EXIT_FAILURE);
  }
  ft_parse_replace_double_by_token(cmd);
  if ((err = ft_parse_check_error(cmd)))
  {
    return (EXIT_FAILURE);
  }
  ft_parse_replace_space(cmd);
  return (EXIT_SUCCESS);
}

int  ft_parse_pop_and_replace_and_check_error(t_arr *tab_cmds)
{
  int index;
  t_arr *cmd;
  int err;

  index = 0;
  while (index < (int)tab_cmds->length)
  {
    cmd = *(t_arr **)(
      (unsigned char *)tab_cmds->ptr + index * tab_cmds->sizeof_elem);
    if ((err = ft_parse_pop_and_replace_and_check_error_switch(cmd)))
    {
      return (EXIT_FAILURE);
    }
    if (!cmd->length)
    {
      ft_arr_free(ft_arr_pop(tab_cmds, index));
    }
    index++;
  }
  return (EXIT_SUCCESS);
}
