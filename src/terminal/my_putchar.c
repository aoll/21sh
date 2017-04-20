/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 12:55:48 by aollivie          #+#    #+#             */
/*   Updated: 2017/04/20 12:58:53 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** it's a function to give in parameter to the function who apply different
** change to the terminal, like tputs()
*/

int	my_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}
