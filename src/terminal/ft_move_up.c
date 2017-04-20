/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:54:10 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:57:15 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** move the cursor to a one up line
*/

int	ft_move_up(void)
{
	char *cmd;

	if ((cmd = tgetstr("up", NULL)) == NULL)
		return (EXIT_FAILURE);
	tputs(cmd, 0, &my_putchar);
	return (EXIT_SUCCESS);
}
