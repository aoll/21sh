/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal_winsize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:44:46 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:48:12 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** take the adress of a struct winsize and if success git it the informations
** of the terminal size
*/

int	ft_terminal_winsize(struct winsize *terminal_size)
{
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char *)terminal_size) < 0)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
