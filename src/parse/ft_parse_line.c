/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 09:31:13 by alex              #+#    #+#             */
/*   Updated: 2017/02/06 15:22:11 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * parsing
 */
t_arr  *ft_parse_line(t_arr *arr)
{
  t_arr *tab_cmds;
  int err;

  if (!(tab_cmds = ft_parse_separate_cmd(arr)))
    return (NULL);
  
  if ((err = ft_parse_pop_and_replace_and_check_error(tab_cmds)))
  {
    if (tab_cmds)
    {
      if (tab_cmds->length)
        ft_arr_free(ft_arr_pop(tab_cmds, 0));
      if (tab_cmds->ptr)
        free(tab_cmds->ptr);
      free(tab_cmds);
      tab_cmds = NULL;
    }
    return (NULL);
  }
  return (tab_cmds);
}
