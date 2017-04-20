/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_basic_video.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:51:26 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:56:48 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** turn off all alternative mode
*/

int	ft_mode_basic_video(void)
{
	char *cmd;

	if ((cmd = tgetstr("me", NULL)) == NULL)
		return (EXIT_FAILURE);
	tputs(cmd, 0, &my_putchar);
	return (EXIT_SUCCESS);
}
