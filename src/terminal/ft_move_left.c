/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:53:22 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:58:08 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** move the cursor to a actual position x - 1 (left)
*/

int	ft_move_left(void)
{
	char *cmd;
	char *new;

	if ((cmd = tgetstr("le", NULL)) == NULL)
		return (EXIT_FAILURE);
	new = ft_strnew(ft_strlen(cmd) + PADDING_BUFFER);
	ft_bzero(new, ft_strlen(cmd) + PADDING_BUFFER);
	ft_memcpy(new, cmd, ft_strlen(cmd));
	tputs(new, 0, &my_putchar);
	return (EXIT_SUCCESS);
}
