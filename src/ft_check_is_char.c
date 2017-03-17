/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_is_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 18:55:26 by alex              #+#    #+#             */
/*   Updated: 2017/03/15 14:53:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** check if char c is present as the first char of str from a t_arr *arr of str
*/

int	ft_check_is_char(t_arr *arr, char c)
{
	int		i;
	char	*s_line;
	int		nb;

	i = 0;
	nb = 0;
	while (i < (int)arr->length)
	{
		s_line = *(char **)((unsigned char *)arr->ptr + i * arr->sizeof_elem);
		if (*s_line == c)
		{
			nb++;
		}
		i++;
	}
	if (nb)
	{
		return (nb % 2);
	}
	return (EXIT_SUCCESS);
}
