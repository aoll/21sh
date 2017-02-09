/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_restore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:00:09 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 18:43:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/**
 * restore the signal
 */

static void  ft_signal_sigint_son(int a)
{
  g_is_ctrl_c_son++;
  exit(0);
  return;
}

int  ft_signal_restore(void)
{
  // int num_sig;
  //
  // num_sig = 1;
  // while (num_sig < NSIG)
  // {
  //   signal(num_sig, SIG_DFL);
  //   num_sig++;
  // }
  signal(SIGINT, SIG_DFL);
  // signal(SIGINT, ft_signal_sigint_son);
  return (EXIT_SUCCESS);
}
