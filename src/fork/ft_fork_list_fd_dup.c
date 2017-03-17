/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_list_fd_dup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:04:43 by alex              #+#    #+#             */
/*   Updated: 2017/03/17 12:10:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** dup the fd from a arr to a other
*/

int	ft_fork_list_fd_dup(t_arr *dst, const t_arr *src)
{
	int				*fd_tmp;
	int				*fd_dup;
	int				index;

	index = 0;
	while (index < (int)src->length)
	{
		fd_tmp = *(int **)(
			(unsigned char *)src->ptr + index * src->sizeof_elem);
		if (!(fd_dup = malloc(sizeof(int))))
		{
			return (EXIT_FAILURE);
		}
		*fd_dup = *fd_tmp;
		ft_arr_push(dst, fd_dup, -1);
		index++;
	}
	return (EXIT_SUCCESS);
}
