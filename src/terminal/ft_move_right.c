/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:53:48 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:54:24 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
**  move the cursor to a actual position x + 1 (right)
*/

int	ft_move_right(void)
{
	char *cmd;

	if ((cmd = tgetstr("nd", NULL)) == NULL)
		return (EXIT_FAILURE);
	tputs(cmd, 0, &my_putchar);
	return (EXIT_SUCCESS);
}
