/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_insertion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:51:37 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:53:12 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** autorize the insertion between caracteres x and x - 1, the cursor don't move
*/

int	ft_mode_insertion(void)
{
	char *cmd;

	if ((cmd = tgetstr("im", NULL)) == NULL)
	{
		return (EXIT_FAILURE);
	}
	tputs(cmd, 0, &my_putchar);
	return (EXIT_SUCCESS);
}
