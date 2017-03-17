/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_list_fd_left_redirect.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:20:39 by alex              #+#    #+#             */
/*   Updated: 2017/02/07 17:20:52 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

/*
** push in t_arr a int * telling is a left redirect
*/

int	ft_fork_list_fd_left_redirect(t_arr *arr_fd_stdin)
{
	int				*fd_dup;

	if (!(fd_dup = malloc(sizeof(int))))
	{
		return (EXIT_FAILURE);
	}
	*fd_dup = D_LEFT_REDIRECT;
	ft_arr_push(arr_fd_stdin, fd_dup, -1);
	return (EXIT_SUCCESS);
}
