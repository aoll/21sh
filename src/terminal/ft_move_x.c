/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:54:57 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:58:21 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** move the cursor to a new position x
*/

int	ft_move_x(int new_pos_x)
{
	char *cmd;

	if ((cmd = tgetstr("ch", NULL)) == NULL)
		return (EXIT_FAILURE);
	tputs(tgoto(cmd, 0, new_pos_x), 0, &my_putchar);
	return (EXIT_SUCCESS);
}
