/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_init_tab_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:27:10 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 13:30:11 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * init a char ** by split with SPACE_SEPARATOR
 */
int  ft_fork_init_tab_cmd(t_fork *st_fork, char *cmd)
{
  ft_array_free(&st_fork->tab_cmd);
  if (!(st_fork->tab_cmd = ft_strsplit(cmd, SPACE_SEPARATOR)))
  {
    return (EXIT_FAILURE);
  }
  if (!st_fork->tab_cmd[0])
  {
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
