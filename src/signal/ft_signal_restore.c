/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_restore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:00:09 by alex              #+#    #+#             */
/*   Updated: 2017/05/18 10:21:27 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** restore the signal
*/

int	ft_signal_restore(void)
{
	// signal(SIGTSTP, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	return (EXIT_SUCCESS);
}
