/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_free_arr_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:52:05 by alex              #+#    #+#             */
/*   Updated: 2017/02/08 13:00:53 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int  ft_arr_free_arr_fd(t_arr_fd *arr_fd)
{
  if (!arr_fd)
  {
    return (EXIT_SUCCESS);
  }
  if (arr_fd->arr_fd_stdout)
    ft_arr_free(arr_fd->arr_fd_stdout);
  if (arr_fd->arr_fd_stderr)
    ft_arr_free(arr_fd->arr_fd_stderr);
  if (arr_fd->arr_fd_stdin)
    ft_arr_free(arr_fd->arr_fd_stdin);
  if (arr_fd->arr_d_end_word)
    ft_arr_free(arr_fd->arr_d_end_word);
  return (EXIT_SUCCESS);
}
