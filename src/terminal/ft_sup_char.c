/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sup_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:55:24 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:59:34 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** delete n character from the current cursor's position
*/

int	ft_sup_char(int n)
{
	char *cmd;
	char *new;

	if ((cmd = tgetstr("dc", NULL)) == NULL)
		return (EXIT_FAILURE);
	new = ft_strnew(ft_strlen(cmd) + PADDING_BUFFER);
	ft_bzero(new, ft_strlen(cmd) + PADDING_BUFFER);
	ft_memcpy(new, cmd, ft_strlen(cmd));
	while (n--)
	{
		tputs(new, 0, &my_putchar);
	}
	return (EXIT_SUCCESS);
}
