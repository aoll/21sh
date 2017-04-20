/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_reverse_video.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:52:08 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:57:18 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** every output after this function will be in reverse mode video
*/

int	ft_mode_reverse_video(void)
{
	char *cmd;

	if ((cmd = tgetstr("mr", NULL)) == NULL)
		return (EXIT_FAILURE);
	tputs(cmd, 0, &my_putchar);
	return (EXIT_SUCCESS);
}
