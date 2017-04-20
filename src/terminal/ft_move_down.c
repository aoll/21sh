/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:52:34 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:57:22 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** move the cursor to a one down line
*/

int	ft_move_down(void)
{
	char *cmd;

	if ((cmd = tgetstr("do", NULL)) == NULL)
		return (EXIT_FAILURE);
	tputs(cmd, 0, &my_putchar);
	return (EXIT_SUCCESS);
}
