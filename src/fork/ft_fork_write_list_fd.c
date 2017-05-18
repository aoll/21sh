/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_write_list_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 19:05:38 by alex              #+#    #+#             */
/*   Updated: 2017/05/18 11:51:06 by aollivie         ###   ########.fr       */
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
		if (*fd == -10)
		{
			*fd = -1;
		}
		else if (*fd < 0)
		{
			*fd *= -1;
		}
		// ft_putstr("\nlist:");
		// ft_putnbr(*fd);
		write(*fd, buff, len);
		index++;
	}
	return (EXIT_SUCCESS);
}
