/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_write_list_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:05:38 by alex              #+#    #+#             */
/*   Updated: 2017/02/07 19:05:54 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** write on a list of fd
*/

int	ft_fork_write_list_fd(t_arr *arr, char *buff, int len)
{
	int				index;
	int				*fd;

	index = 0;
	while (index < (int)arr->length)
	{
		fd = *(int **)((unsigned char *)arr->ptr + index * arr->sizeof_elem);
		write(*fd, buff, len);
		index++;
	}
	return (EXIT_SUCCESS);
}
