/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_nb_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:50:08 by alex              #+#    #+#             */
/*   Updated: 2017/02/09 13:50:29 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** return the number of pipe
*/

int	ft_fork_nb_pipe(t_arr *arr)
{
	int				index;
	int				nb_pipe;
	char			*s_line;

	index = 0;
	nb_pipe = 0;
	while (index < (int)arr->length)
	{
		s_line = *(char **)(
			(unsigned char *)arr->ptr + index * arr->sizeof_elem);
		if (*s_line == PIPE)
		{
			nb_pipe++;
		}
		index++;
	}
	return (nb_pipe);
}
