/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_init_new_arr_line.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 18:31:05 by alex              #+#    #+#             */
/*   Updated: 2017/02/05 18:46:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * init a t_arr *arr with char *s as elem
 */
int  ft_parse_init_new_arr_line(t_arr **arr)
{
  t_arr *cmd;

  cmd = *arr;
  cmd = ft_arr_new(1, sizeof(char *));
  cmd->f_del = &ft_memdel;
  cmd->f_print = &ft_arr_putchar;
  *arr = cmd;
  return (EXIT_SUCCESS);
}
