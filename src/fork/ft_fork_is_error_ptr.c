/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_is_error_ptr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:05:33 by alex              #+#    #+#             */
/*   Updated: 2017/02/08 16:10:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** check if error_ptr is set and write it on stderr and exit process
*/

int	ft_fork_is_error_ptr(char **error_ptr, t_arr_fd *arr_fd)
{
	if (!error_ptr)
	{
		return (EXIT_SUCCESS);
	}
	if (*error_ptr)
	{
		ft_putstr_fd(*error_ptr, STDERR);
		ft_str_free(error_ptr);
		ft_arr_close_arr_fd(arr_fd);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
