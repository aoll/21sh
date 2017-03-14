/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:47:00 by alex              #+#    #+#             */
/*   Updated: 2017/02/10 13:34:49 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

// static void  ft_signal_print(int num_sig)
// {
//   ft_putstr("\nsignal:");
//   ft_putnbr(num_sig);
//   ft_putstr(".\n");
//   return;
// }

/*
 *
 */
void  ft_signal_sigint_not_env(int num_sig)
{
  (void)num_sig;
  g_is_ctrl_c_father++;
  ft_putstr("\n$> ");
  return;
}
void  ft_signal_sigint_chariot(int num_sig)
{
  (void)num_sig;
  ft_putstr("\n");
  return;
}
void  ft_signal_sigint_c(int num_sig)
{
  (void)num_sig;
  // ft_putstr("\n^C\n");
  g_is_ctrl_c_father++;
  return;
}
/*
 * init the signal
 */
int  ft_signal_init(void)
{
  int num_sig;

  num_sig = 1;
  while (num_sig < NSIG)
  {
    signal(num_sig, SIG_IGN); //ignored
    num_sig++;
  }
  g_is_ctrl_c_father = 0;
  signal(SIGINT, ft_signal_sigint_c);
  return (EXIT_SUCCESS);
}
