/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_char_between_two_chariot.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 08:54:26 by alex              #+#    #+#             */
/*   Updated: 2017/03/13 08:54:45 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** nombre de char between two '\n' from the index in parameter to the first '\n'
** founded or the begin of the line
*/

int	ft_nb_char_between_two_chariot(t_arr *arr, int index)
{
	int				nb_char;
	unsigned char	*s_line;

	nb_char = 0;
	while (index >= 0)
	{
		s_line = (unsigned char *)arr->ptr + arr->sizeof_elem * (index);
		s_line = *(unsigned char **)s_line;
		if (*s_line == 10)
		{
			return (nb_char);
		}
		nb_char++;
		index--;
	}
	return (nb_char);
}
