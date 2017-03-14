/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_restore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:00:09 by alex              #+#    #+#             */
/*   Updated: 2017/02/10 13:35:37 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
 * restore the signal
 */

  // static void  ft_signal_sigint_son(int a)
  // {
  //   exit(0);
  //   return;
  // }

int  ft_signal_restore(void)
{
  signal(SIGINT, SIG_DFL);
  return (EXIT_SUCCESS);
}
